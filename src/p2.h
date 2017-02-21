#ifndef P2_H
#define P2_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <map>
struct evl_token
{
	enum token_type
	{
		NAME, NUMBER, SINGLE
	};
	token_type type;
	std::string str;

	int line_no;
};
typedef std::list<evl_token> evl_tokens;
struct evl_statement
{
	enum statement_type
	{
		MODULE, WIRE, COMPONENT, ENDMODULE,ASSIGN
	};

	statement_type type;
	evl_tokens tokens;

};
int componet_num;
typedef std::list<evl_statement> evl_statements;
int wires_num;
struct evl_wire
{
	std::string name;
	int width;
};	//	struct evl_wire

typedef std::list<evl_wire> evl_wires;
typedef std::map<std::string, int> evl_wires_table;
struct evl_pin
{
	std::string name;
	int lsb;
	int msb;
};
typedef std::list<evl_pin> pins;
struct evl_componet
{
	std::string type;
	std::string name;
	pins pin2;
};	//	struct evl_wire

typedef std::list<evl_componet> evl_componets;

struct assign
{

	pins pin2;
};	//	struct evl_wire

typedef std::list<assign> assigns;



bool extract_tokens_from_line(std::string line, int line_no, std::list<evl_token> &tokens)
{ // use reference to modify it
	for (size_t i = 0; i < line.size(); ) {
		if (line[i] == '/')
		{
			++i;
			if ((i == line.size()) || (line[i] != '/'))
			{
				std::cerr << "LINE " << line_no
					<< ": a single / is not allowed" << std::endl;
				return false;
			}
			break; // skip the rest of the line by exiting the loop
		}

		// spaces
		else if ((line[i] == ' ') || (line[i] == '\t')
			|| (line[i] == '\r') || (line[i] == '\n'))
		{
			++i; // skip this space character
				 // skip the rest of the iteration
		}
		else if ((line[i] == '(') || (line[i] == ')')
			|| (line[i] == '[') || (line[i] == ']')
			|| (line[i] == ':') || (line[i] == ';')
			|| (line[i] == ',')|| (line[i] == '='))
		{
			evl_token token;
			token.line_no = line_no;
			token.type = evl_token::SINGLE;
			token.str = std::string(1, line[i]);
			tokens.push_back(token);
			++i;

		}
		else if (((line[i] >= 'a') && (line[i] <= 'z'))       // a to z
			|| ((line[i] >= 'A') && (line[i] <= 'Z'))    // A to Z
			|| (line[i] == '_'))
		{ // a NAME token 
			evl_token token; token.line_no = line_no;
			token.type = evl_token::NAME;
			size_t name_begin = i;
			for (++i; i < line.size(); ++i)
			{
				if (!(((line[i] >= 'a') && (line[i] <= 'z'))
					|| ((line[i] >= 'A') && (line[i] <= 'Z'))
					|| ((line[i] >= '0') && (line[i] <= '9'))
					|| (line[i] == '_') || (line[i] == '$')))
				{
					break; // [name_begin, i) is the range for the token
				}
			}
			token.str = line.substr(name_begin, i - name_begin);
			tokens.push_back(token);


		}
		else if ((line[i] >= '0') && (line[i] <= '9'))
		{ // a NAME token 
			evl_token token; token.line_no = line_no;
			token.type = evl_token::NUMBER;
			size_t number_begin = i;
			for (++i; i < line.size(); ++i)
			{
				if ((line[i]<'0') || (line[i]>'9'))
				{
					break; // [name_begin, i) is the range for the token
				}
			}
			token.str = line.substr(number_begin, i - number_begin);
			tokens.push_back(token);

		}
		else
		{
			std::cerr << "LINE " << line_no
				<< ": invalid character" << std::endl;
			return false;
		}
	}
	return true; // nothing left
}

bool extract_tokens_from_file(std::string file_name, std::list<evl_token> &tokens)
{ // use reference to modify it
	std::ifstream input_file(file_name.c_str());
	if (!input_file) {
		std::cerr << "I can¡¯t read " << file_name << "." << std::endl; return false;
	}
	tokens.clear(); // be defensive, make it empty 
	std::string line;
	for (int line_no = 1; std::getline(input_file, line); ++line_no)
	{
		if (!extract_tokens_from_line(line, line_no, tokens))
		{
			return false;
		}
	}
	return true;

}




void display_tokens(std::list<evl_token> &tokens) {
	for (evl_tokens::iterator it = tokens.begin(); it != tokens.end(); ++it) {
		if (it->type == evl_token::SINGLE)
		{
			std::cout << "SINGLE " << it->str << std::endl;
		}
		else if (it->type == evl_token::NAME)
		{
			std::cout << "NAME " << it->str << std::endl;
		}
		else { // must be NUMBER 
			std::cout << "NUMBER " << it->str << std::endl;
		}
	}
}

bool store_tokens_to_file(std::string file_name, std::list<evl_token> &tokens) {
	std::ofstream output_file(file_name.c_str());
	if (!output_file)
	{
		std::cerr << "I can't write " << file_name << ".tokens ." << std::endl;
		return false;
	}
	// almost the same loop as display_tokens
	return true;
}


bool group_tokens_into_statements(evl_statements &statements, evl_tokens &tokens,std::string &module_name) {
	for (; !tokens.empty();)
	{ // generate one statement per iteration 
		evl_token token = tokens.front();
		if (token.type != evl_token::NAME)
		{
			std::cerr << "Need a NAME token but found ¡¯" << token.str << "¡¯ on line " << token.line_no << std::endl;
			return false;
		} if (token.str == "module")
		{
			evl_statement module;
			module.type = evl_statement::MODULE;
			// Thinking of a function to replace the loop? 
			for (; !tokens.empty();)
			{
				if (tokens.front().str != "module"&&tokens.front().type == evl_token::NAME) {
					module_name = tokens.front().str;
				}
				module.tokens.push_back(tokens.front());

				tokens.pop_front(); // consume one token per iteration 
				if (module.tokens.back().str == ";")
					break; // exit if the ending ";" is found 
			} if (module.tokens.back().str != ";")
			{
				std::cerr << "Look for ¡¯;¡¯ but reach the end of file" << std::endl; return false;
			}
			statements.push_back(module);
		}
		else if
			(token.str == "endmodule") {
			evl_statement endmodule;
			endmodule.type = evl_statement::ENDMODULE;
			endmodule.tokens.push_back(token);
			tokens.pop_front();
			statements.push_back(endmodule);

		}
		else if (token.str == "wire")
		{
			evl_statement wire;
			wire.type = evl_statement::WIRE;

			//Thinking of a function to replace the loop?
			for (; !tokens.empty();)
			{
				if (tokens.front().type == evl_token::NAME&&tokens.front().str != "wire")
				{
					wires_num++;
				}
				wire.tokens.push_back(tokens.front());
				//std::cout << wire.tokens.back().str << std::endl;
				tokens.pop_front(); //consume one token per iteration

				if (wire.tokens.back().str == ";")
				{
					break;	  		//exit if the ending ";" is found
				}
			}
			if (wire.tokens.back().str != ";")
			{
				std::cerr << "Look for ';' but reach the end of file " << std::endl;
				return false;
			}
			statements.push_back(wire);
		}

		else if (token.str == "assign")
		{
			evl_statement assign;
			assign.type = evl_statement::ASSIGN;

			//Thinking of a function to replace the loop?
			for (; !tokens.empty();)
			{
				
				assign.tokens.push_back(tokens.front());
				//std::cout << wire.tokens.back().str << std::endl;
				tokens.pop_front(); //consume one token per iteration

				if (assign.tokens.back().str == ";")
				{
					break;	  		//exit if the ending ";" is found
				}
			}
			if (assign.tokens.back().str != ";")
			{
				std::cerr << "Look for ';' but reach the end of file " << std::endl;
				return false;
			}
			statements.push_back(assign);
		}

		else
		{
			evl_statement component;
			component.type = evl_statement::COMPONENT;

			//Thinking of a function to replace the loop?
			for (; !tokens.empty();)
			{
				component.tokens.push_back(tokens.front());
				//std::cout << component.tokens.back().str << std::endl;
				tokens.pop_front(); //consume one token per iteration

				if (component.tokens.back().str == ";")
				{
					componet_num++;
					break;	  		//exit if the ending ";" is found
				}
			}
			//std::cout << component.tokens.size() << std::endl;
			if (component.tokens.back().str != ";")
			{
				std::cerr << "Look for ';' but reach the end of file " << std::endl;
				return false;
			}
			statements.push_back(component);
		}
	}
	return true;
}


 bool process_wire_statement(evl_wires &wires, evl_statement &s) {
	enum state_type { INIT, WIRE, DONE, WIRES, WIRE_NAME, BUS, BUS_MSB, BUS_COLON, BUS_DONE };
	state_type state = INIT;
	int bus_width = 1;
	for (; !s.tokens.empty() && (state != DONE);
		s.tokens.pop_front()) {
		evl_token t = s.tokens.front();
		if (state == INIT) {
			if (t.str == "wire") { state = WIRE; }
			else {
				std::cerr << "Need ¡¯wire¡¯ but found ¡¯" << t.str << "¡¯ on line " << t.line_no << std::endl;
				return false;
			}

		}
		else if (state == WIRE) {
			if (t.str == "[") {
				state = BUS;

			}
			else if (t.type == evl_token::NAME) {
				evl_wire wire;
				wire.name = t.str;
				wire.width = bus_width;
				wires.push_back(wire);
				state = WIRE_NAME;
			}
			else {
				std::cerr << "Need NAME but found ¡¯" << t.str << "¡¯ on line " << t.line_no << std::endl;
				return false;
			}
		}
		else if (state == WIRES) {
			if (t.type == evl_token::NAME) {
				evl_wire wire;
				wire.name = t.str;
				wire.width = bus_width;
				wires.push_back(wire);
				state = WIRE_NAME;
			}
			else {
				std::cerr << "Need NAME but found ¡¯" << t.str << "¡¯ on line " << t.line_no << std::endl;
				return false;
			}
		}
		else if (state == WIRE_NAME) {
			if (t.str == ",") {
				state = WIRES;

			}
			else if (t.str == ";")
			{
				bus_width = 1;
				state = DONE;
			}
			else return false;
		}

		else if (state == BUS) {
			if (t.type == evl_token::NUMBER) {
				bus_width = atoi(t.str.c_str()) + 1;
				state = BUS_MSB;
			}
			else return false;
		}
		else if (state == BUS_MSB) {
			if (t.str == ":") {
				state = BUS_COLON;

			}
			else return false;
		}
		else if (state == BUS_COLON)
		{
			if (t.type == evl_token::NUMBER) {
				bus_width = bus_width - atoi(t.str.c_str());
				state = BUS_DONE;
			}
			else return false;

		}

		else if (state == BUS_DONE)
		{
			if (t.str == "]")
			{
				state = WIRE;
			}
			else return false;
		}



	} if (!s.tokens.empty() || (state != DONE))
	{
		std::cerr << "something wrong with the statement" << std::endl;
		return false;
	}
	return true;
}
 bool process_assign_statement(assign &assign, evl_statement &s) {
	 enum state_type {
		 INIT, LHS, LHS_NAME, LHS_BUS, LHS_MSB, LHS_COLON, LHS_LSB, LHS_DONE, RHS, RHS_NAME, RHS_BUS, RHS_MSB, RHS_COLON,RHS_LSB,RHS_DONE,DONE
	 };
	 state_type state = INIT; 

	 for (; !s.tokens.empty() && (state != DONE);
		 s.tokens.pop_front()) {
		 evl_token t = s.tokens.front();
		 if (state == INIT) {
			 if (t.str == "assign") { state = LHS; }
			 else {
				 std::cerr << "Need ¡¯wire¡¯ but found ¡¯" << t.str << "¡¯ on line " << t.line_no << std::endl;
				 return false;
			 }
		 }
		 else if (state == LHS) {
			 if (t.type == evl_token::NAME)
			 {
				 evl_pin pin;
				 pin.name = t.str;
				 pin.lsb = -1;
				 pin.msb = -1;
				 assign.pin2.push_back(pin);
				 state = LHS_NAME;
			 }
		 }
			 else if (state == LHS_NAME) {
				 if (t.str == "[")
				 {
					 state = LHS_BUS;
				 }
				 if (t.str == "=") {
					 state = RHS;
				 }
			 }
				 else if (state == LHS_BUS){
					 assign.pin2.back().msb = atoi(t.str.c_str());
					 state = LHS_MSB;
				 }
				 else if (state == LHS_MSB) {
					 if (t.str == "]")
					 {
						 state = LHS_DONE;
					 }
					 if (t.str == ":") {
						 state = LHS_COLON;
					 }
				 }
				 else if (state == LHS_COLON) {
					 assign.pin2.back().lsb = atoi(t.str.c_str());
					 state = LHS_LSB;
				 }
				 else if (state == LHS_LSB) {
					 if (t.str == "]")
					 {
						 state = LHS_DONE;
					 }
				 }
				 else if (state == LHS_DONE) {
					 if (t.str == "=") {
						 state = RHS;
					 }
				 }

				 else if (state ==RHS) {
					 if (t.type == evl_token::NAME){
						 evl_pin pinr;
						 pinr.name = t.str;
						 pinr.lsb = -1;
						 pinr.msb = -1;
						 assign.pin2.push_back(pinr);
						 state = RHS_NAME;
						 
					 }
				 }
				 else if (state == RHS_NAME) {
					 if (t.str == "[") {
						 state = RHS_BUS;
					 }
					 if (t.str == ";") {
						 state = DONE;
					 }
				 }

				 else if (state == RHS_BUS) {
					 assign.pin2.back().msb = atoi(t.str.c_str());
					 state = RHS_MSB;
				 }
				 else if (state == RHS_MSB) {
					 if (t.str == ":") {
						 state = RHS_COLON;
					 }
					 if (t.str == "]") {
						 state = RHS_DONE;
					 }
				 }
				 else if (state == RHS_COLON) {
					 assign.pin2.back().lsb = atoi(t.str.c_str());
					 state = RHS_LSB;
				 }
				 else if (state == RHS_LSB) {
					 if (t.str == "]") {
						 state = DONE;
					 }
				 }
				
			 }
			 return true;
 }

bool process_componet_statement(evl_componet &comp, evl_statement &s) {
	enum state_type {
		INIT, TYPE, DONE, WIRES, NAME, PINS, PINS_NAME, PINS_DONE, BUS, BUS_MSB, BUS_COLON, BUS_DONE, BUS_LSB
	};
	state_type state = INIT;


	for (; !s.tokens.empty() && (state != DONE);
		s.tokens.pop_front()) {
		evl_token t = s.tokens.front();
		if (state == INIT) {
			if (t.type == evl_token::NAME)
			{

				comp.type = t.str;
				comp.name = " ";
				state = TYPE;
			}

			else {
				std::cerr << "Need NAME but found ¡¯" << t.str << "¡¯ on line " << t.line_no << std::endl;
				return false;
			}

		}

		else if (state == TYPE)
		{
			if (t.str == "(") {
				state = PINS;
			}
			else if (t.type == evl_token::NAME)
			{

				comp.name = t.str;
				state = NAME;
			}

		}

		else if (state == NAME) {
			if (t.str == "(") {
				state = PINS;
			}

		}

		else if (state == PINS) {
			if (t.type == evl_token::NAME) {
				evl_pin pin;
				pin.name = t.str;
				pin.lsb = -1;
				pin.msb = -1;
				comp.pin2.push_back(pin);
				state = PINS_NAME;
			}
			else return false;
		}

		else if (state == PINS_NAME) {
			if (t.str == ",")
			{
				state = PINS;
			}
			else if (t.str == "[")
			{
				state = BUS;
			}
			else if (t.str == ")")
			{
				state = PINS_DONE;
			}


			else {
				std::cerr << "Need PIN but found ¡¯" << t.str << "¡¯ on line " << t.line_no << std::endl;
				return false;
			}

		}
		else if (state == BUS) {
			comp.pin2.back().msb = atoi(t.str.c_str());
			state = BUS_MSB;
		}
		else if (state == BUS_MSB) {

			if (t.str == ":") {
				state = BUS_COLON;
			}
			else if (t.str == "]") {
				state = BUS_DONE;
			}
			else return false;
		}
		else if (state == BUS_COLON) {
			comp.pin2.back().lsb = atoi(t.str.c_str());
			state = BUS_LSB;
		}


		else if (state == BUS_LSB) {


			if (t.str == "]") {
				state = BUS_DONE;
			}
		}
		else if (state == BUS_DONE) {
			if (t.str == ")") {
				state = PINS_DONE;
			}
			else if (t.str == ",") {
				state = PINS;
			}
			else return false;
		}

		else if (state == PINS_DONE) {
			if (t.str == ";") {
				state = DONE;
			}
			else return false;
		}

		else return false;


	}
	return true;
}


void display_statements(std::string file_name, evl_statements &statements,evl_wires &wires, evl_componets &comps) {
	evl_statements store;
	std::ofstream output_file2(file_name.c_str());
	if (!output_file2)
	{
		std::cerr << "I can't write " << file_name.c_str() << ".tokens ." << std::endl;
	}
	for (; !statements.empty(); statements.pop_front()) {
		evl_statement temp = statements.front();
		//std::cout << temp.tokens.front().str << "  " << std::endl;
		if (temp.type == evl_statement::MODULE) {
			for (; !temp.tokens.empty(); temp.tokens.pop_front()) {
				if (temp.tokens.front().type == evl_token::NAME) {
					output_file2 << temp.tokens.front().str << " ";
				}
			}
			output_file2 << " " << std::endl;
		}

		else if (temp.type == evl_statement::ENDMODULE) {
			store.push_back(temp);

		}
		else if (temp.type == evl_statement::WIRE) {
			evl_wires diswire;


			if (process_wire_statement(diswire, temp)) {
				if (wires_num > 0) {
					output_file2 << "wires" << " " << wires_num << std::endl;
					wires_num = -1;
				}
				for (; !diswire.empty(); diswire.pop_front()) {

					output_file2 << "wire" << " " << diswire.front().name << " " << diswire.front().width << std::endl;
					wires.push_back(diswire.front());
				}

			}
		}


		else if (temp.type == evl_statement::COMPONENT) {
			store.push_back(temp);
			
		} 

		else if (temp.type == evl_statement::ASSIGN) {
			assign as;
			if (!process_assign_statement(as, temp)) {
				return ;
			}
			evl_componet at;
			at.type = "assign";
			at.name = "";
			std::cout << at.type << " ";
			for (;!as.pin2.empty(); as.pin2.pop_front())
			{
				at.pin2.push_back(as.pin2.front());
				std::cout << at.pin2.back().name << " "<< at.pin2.back().lsb<<" " << at.pin2.back().msb;
				std::cout << " " << std::endl;
			}
			comps.push_back(at);
			
		}
		
	}
	for (; !store.empty(); store.pop_front()) {
		evl_statement temp = store.front();
		if (temp.type == evl_statement::ENDMODULE) {
			if (temp.tokens.front().type == evl_token::NAME) {
				output_file2 << temp.tokens.front().str << std::endl;

			}
		}
		else if (temp.type == evl_statement::COMPONENT) {
			
			evl_componet comp;

			if (process_componet_statement(comp, temp)) {

				std::cout << comp.type << std::endl;
			}
			if (componet_num > 0)
			{
				output_file2 << "components" << " " << componet_num << std::endl;
				componet_num = -1;
			}

			evl_componet t = comp;
			comps.push_back(t);
			if (t.name == " ")
			{
				output_file2 << "component" << " " << t.type << " " << t.pin2.size() << std::endl;
			}
			else {
				output_file2 << "component" << " " << t.type << " " << t.name << " " << t.pin2.size() << std::endl;
			}
			for (; !t.pin2.empty(); t.pin2.pop_front()) {
				//std::cout << t.pin2.front().name << " " << t.pin2.front().msb << " " << t.pin2.front().lsb << std::endl;
				if (t.pin2.front().lsb >= 0)
				{
					if (t.pin2.front().msb < 0) {
						output_file2 << "  " << "pin " << t.pin2.front().name << " " << t.pin2.front().lsb << std::endl;
					}
					else
					{
						output_file2 << "  " << "pin " << t.pin2.front().name << " " << t.pin2.front().msb << " " << t.pin2.front().lsb << std::endl;
					}
				}
				else if (t.pin2.front().msb >= 0)
				{
					output_file2 << "  " << "pin " << t.pin2.front().name << " " << t.pin2.front().msb << std::endl;
				}
				else {
					output_file2 << "  " << "pin " << t.pin2.front().name << std::endl;
				}

			}


		}

	}




}

bool parse_evl_file(std::string evl_file, std::string &module_name, evl_wires &wires, evl_componets &comps) {
	
	evl_tokens tokens;
	if (!extract_tokens_from_file(evl_file, tokens)) {
		return false;
	}
	//display_tokens(tokens);
	if (!store_tokens_to_file(evl_file + ".tokens", tokens))
	{
		return false;
	}
	evl_statements statements;
	
	if (!group_tokens_into_statements(statements, tokens, module_name))
	{
		return false;
	}
	  display_statements(evl_file + ".syntax", statements,wires,comps);
	
	return true;
	
}




#endif