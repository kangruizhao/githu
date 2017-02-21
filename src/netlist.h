#ifndef GUARD_NETLIST_H 
#define GUARD_NETLIST_H
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <assert.h>
#include <map>
#include "p2.h"
class netlist; 
class gate; 
class net; 
class pin3;
class net {
public:
	std::string name_; // e.g. "a", "s[0]" 
	int signal_; // e.g. ¡¯0¡¯ or ¡¯1¡¯ 
	int times;
	std::vector<std::list<int> > signals_;
	net(std::string name) : name_(name) { signal_ = 3; times = -1; };
	void getvalue(int number);
	std::list<pin3 *> connections_; // relationship "connect" 
	void append_pin(pin3 *p);
	int decide(int a, int b);
}; // class net
class pin3 {
public:
		char dir_; // e.g. ¡¯I¡¯ or ¡¯O¡¯ 
		int logic;
		int ptime;
		int out;
		gate *gate_; // relationship "contain" 
		gate *asout;
		size_t index_; // attribute of "contain" n
		net *net_;
		pin3() { ptime = -1; };// relationship "connect"
		std::vector<net *> bus_;
		bool create(gate *g, size_t index, const evl_pin &p, const std::map<std::string, net *> &nets_table);
	}; // class pin
class gate {
	public:
	std::string name_; std::string type_; // e.g. "and", "or"
	std::string sub;
	int visited;
	std::vector<pin3 *> pins_; 
	std::vector<pin3 *> inputs_;
	std::vector<pin3 *> outputs_;
	gate():name_(""),type_(""){}
	bool create( evl_componet &c, const std::map<std::string, net *> &nets_table, const evl_wires_table &wires_table);
	bool create_pin(evl_pin &ep, size_t index, const std::map<std::string, net *> &nets_table, const evl_wires_table &wires_table);// relationship "contain" 
	gate(std::string type, std::string name) : name_(name), type_(type) {}
	virtual bool validate_structural_semantics();
	virtual void  compute_output();
	virtual void  setinput(std::string filename);
	virtual void  setup(std::string filename);
	virtual void  compute_next_state();
	
	
}; // class gate
class netlist {
public:
	std::string filename;
	std::list<gate *> gates_;
	std::list<net *> nets_; 
	std::map<std::string, net *> nets_table_;

	void create_net(std::string net_name);
	bool create_nets( const evl_wires &wires);
	bool create_gate( evl_componet &c, const evl_wires_table &wires_table);
	bool create_gates(  evl_componets &comps, const evl_wires_table &wires_table);
	bool create( const evl_wires &wires,  evl_componets &comps, const evl_wires_table &wires_table) ;
	void save(std::string file_name, std::string module_name);
	void simulate(std::string file_name, int cycles);

}; // class netlist

class clock_gate : public gate {
	void compute_output();
	clock_gate(std::string name) :gate("evl_clock", name) {};
	bool validate_structural_semantics();

};

class assign_ :public gate {
public :
	assign_(std::string name) :gate("assign", name) { };
	bool validate_structural_semantics();
	void  compute_output();
};

class logic_gate : public gate {
	virtual int evaluate(const std::vector<int> &inputs) = 0;
	
protected: logic_gate(std::string type, std::string name) :gate(type, name) { sub = "logic"; visited = 1; };

public: void compute_output();
		
		bool validate_structural_semantics();
		
};

class buf_gate : public logic_gate {
	virtual int evaluate(const std::vector<int> &inputs);
public:
	buf_gate(std::string name) :logic_gate("buf", name) {}
};

class not_gate : public logic_gate {
	 int evaluate(const std::vector<int> &inputs);
public:
	not_gate(std::string name) :logic_gate("not", name) {}
};


class xor_gate : public logic_gate {
	 int evaluate(const std::vector<int> &inputs);
public:
	xor_gate(std::string name) :logic_gate("xor", name) {}
};

class and_gate : public logic_gate { 
	 int evaluate(const std::vector<int> &inputs); 
public:
	and_gate(std::string name):logic_gate("and",name){}
	
};
class or_gate : public logic_gate {
	 int evaluate(const std::vector<int> &inputs);
public:
	or_gate(std::string name) :logic_gate("or", name) {}
};
class flip_flop : public gate {
	int state_;
	int next_state_;
public:
	flip_flop(std::string name) : gate("evl_dff", name), state_(0), next_state_(0) { } 
	void compute_next_state();
	bool validate_structural_semantics();
	void compute_output();
};



class evl_one : public gate {
	
public:	evl_one(std::string name) : gate("evl_one", name){ }
	void compute_output();
	bool validate_structural_semantics();
};

class evl_zero : public gate {

public:evl_zero(std::string name) : gate("evl_zero", name) { }
	void compute_output();
	bool validate_structural_semantics();
};

class output :public gate {
	std::list<std::string> result;
public:	output(std::string name) : gate("evl_output", name) { }
		void compute_output();
		void setup(std::string filename);
		bool validate_structural_semantics();
};

class evl_input :public gate {
	int transit;
	int npins;
	std::vector<int> pin_width;
	std::vector<long> pin_state;
	std::vector<std::list<long> > pin_states;
	std::list<int> nTransit;
	
public:	evl_input(std::string name) : gate("evl_input", name) { }
		void setinput(std::string filename);
		bool validate_structural_semantics();
		void compute_output();
};

class evl_lut : public gate {
private:
	int word_width, address_width;
	std::vector<int> lut;
public:
	evl_lut(std::string name) :gate("evl_lut", name) {}
	bool validate_structural_semantics();
	void setinput(std::string filename);
	void compute_output();
};

class tris_gate : public logic_gate {
public :
	tris_gate(std::string name) :logic_gate("tris", name) {}
	
	 int evaluate(const std::vector<int> &inputs);
};


void gate::setinput(std::string filename) {

}
void gate::setup(std::string filename) {


}
void  gate::compute_next_state() {

}
bool gate::validate_structural_semantics() {

	return true;// should be provided by derived classes return false; 
}

bool assign_::validate_structural_semantics() {
	pins_[0]->dir_ = 'O';
	pins_[0]->asout = this;
	return true;
}


bool evl_one::validate_structural_semantics() {
	for (size_t i = 0; i < this->pins_.size(); i++)
	{
		outputs_.push_back(pins_[i]);
		pins_[i]->dir_ = 'O';
		pins_[i]->asout = this;
	}
	return true;
}
bool evl_zero::validate_structural_semantics() {
	for (size_t i = 0; i < this->pins_.size(); i++)
	{
		outputs_.push_back(pins_[i]);
		pins_[i]->dir_ = 'O';
		pins_[i]->asout = this;
	}
	return false;
}





bool evl_lut::validate_structural_semantics() {
	pins_[0]->dir_ = 'O';
	pins_[0]->asout = this;
	
	for (size_t i = 1; i < this->pins_.size(); i++)
	{
		inputs_.push_back(pins_[i]);
		pins_[i]->dir_ = 'I';
	}

	return true; 

}

bool logic_gate::validate_structural_semantics() {
	
	outputs_.push_back(pins_[0]);
	pins_[0]->dir_ = 'O';
	pins_[0]->asout = this;
	for (size_t i = 1 ;i < this->pins_.size(); i++)
	{
		inputs_.push_back(pins_[i]);
		pins_[i]->dir_ = 'I';
	}
	
	return true;
}


bool flip_flop::validate_structural_semantics() { 
	if (pins_.size() != 3)
		return false; 
	outputs_.push_back(pins_[0]);
	pins_[0]->dir_ = 'O';
	pins_[0]->asout = this;
	inputs_.push_back(pins_[1]);
	pins_[1]->dir_ = 'I';
	inputs_.push_back(pins_[2]);
	pins_[2]->dir_ = 'I';
	return true; }

bool evl_input:: validate_structural_semantics() {
	if (pins_.empty()) // have at least 1 pin
	{
		return false;
	}
	else
	{
		for (size_t i=0; i<pins_.size(); i++)
		{
			outputs_.push_back((pins_[i]));
			pins_[i]->asout = this;
			pins_[i]->dir_ = 'O';
		}
	}
	return true;
}

bool output::validate_structural_semantics() {
	if (pins_.empty()) // have at least 1 pin
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i<pins_.size(); i++)
		{
			outputs_.push_back((pins_[i]));
			pins_[i]->asout = this;
			pins_[i]->dir_ = 'I';
		}
	}
	return true;
}

bool clock_gate::validate_structural_semantics() {
	if (pins_.empty()) // have at least 1 pin
	{
		return false;
	}
	else
	{
		for (size_t i = 0; i<pins_.size(); i++)
		{
			outputs_.push_back((pins_[i]));
			pins_[i]->asout = this;
			pins_[i]->dir_ = 'O';
		}
	}
	return true;
}



void gate::compute_output() {
	// should be provided by derived classes return false; 
}

void clock_gate::compute_output() {
	pins_[0]->net_->times++;
	return;
}
void evl_lut::setinput(std::string filename) {
	std::string file_name = filename + "." + name_ + ".evl_lut";
	std::ifstream ifs(file_name.c_str());
	assert(ifs.is_open());

	std::string line;
	std::string word;
	getline(ifs, line);
	std::stringstream ss(line);
	ss >> word_width; 
	ss >> address_width;
	while (getline(ifs, line)) {
		std::stringstream ss(line);
		ss >> word;
		char *ret;
		long value = strtol(word.c_str(), &ret, 16);
		assert(ret != NULL);
		lut.push_back((int)value);
	}
	


}

void evl_lut::compute_output() {
	int address = 0;
	int  value = 0;
	pin3* pin_address = pins_[1];
	//std::cout <<pin_address->bus_.size() << std::endl;
	for (int i = pin_address->bus_.size()-1; i >=0; i--) {
		address = address * 2 + (pin_address->bus_[i]->signal_);
		
	}
	if (address < lut.size()) {
		value = lut[address];
	}
	//std::cout << value << std::endl;
	
	pin3* pin_out = pins_[0];
	for (size_t i = 0; i < pin_out->bus_.size(); i++) {
		pin_out->bus_[i]->signal_ = value & 1;
		pin_out->bus_[i]->times++;
		int a = pin_out->bus_[i]->times;
		/*if (a < 1000) {
			pin_out->bus_[i]->signals_[a].push_back(pin_out->bus_[i]->signal_);
		}*/
		value=value >> 1;
	} 
	pin_out->ptime++;

}




void evl_input:: setinput(std::string filename) {
	std::string make_name = filename + "." + name_ + ".evl_input";
	std::ifstream ifs(make_name.c_str());
	 
	assert(ifs.is_open());
	
	std::string line;
	std::string word;
	getline(ifs, line);
	std::stringstream ss(line);
	ss >> npins;


	for (int i = 0; i<npins; i++) {
		std::list<long> theStates;
		int width;
		ss >> width;
		pin_width.push_back(width);
		pin_state.push_back(0);
		pin_states.push_back(theStates);
	}
	while (getline(ifs, line)) {

		std::stringstream ss(line);

		int theTransit;
		ss >> theTransit;
		
		nTransit.push_back(theTransit);
		int a = 1;
		for (int i = 0; i<npins; i++) {
			ss >> word;
			
			char *ret;
			
			long theState = strtol(word.c_str(), &ret, 16);
			
			assert(ret != NULL);
			pin_states[i].push_back(theState);
			
		}
		
	}
	
if (ifs.is_open()) ifs.close();
for (int i = 0; i < npins; i++) {
	if (pin_width[i] == 1) {
		pins_[i]->net_->signal_ = pin_states[i].front() & 1;
		pins_[i]->net_->times++;
		int a = pins_[i]->net_->times;
		pin_states[i].pop_front();
		/*if (a < 1000) {
			pins_[i]->net_->signals_[a].push_back(pins_[i]->net_->signal_);
		}*/
	}
	else {
		for (size_t j = 0; j<pins_[i]->bus_.size(); j++) {

			pins_[i]->bus_[j]->signal_ = pin_states[i].front() & 1;
			pins_[i]->bus_[j]->times++;
			
				int a = pins_[i]->bus_[j]->times;
				/*if (a < 1000) {
					pins_[i]->bus_[j]->signals_[a].push_back(pins_[i]->bus_[j]->signal_);
				}*/
			pin_states[i].front()=pin_states[i].front()>>1;
		}
		pin_states[i].pop_front();
	}
}
if (!nTransit.empty()) {
	transit = nTransit.front();
	nTransit.pop_front();
	transit--;
}
	
}

void evl_input::compute_output() {
	if (nTransit.empty()) {
		/*for (int i = 0; i < npins; i++) {
			if (pin_width[i] == 1) {
				pins_[i]->net_->times++;
			}
			else {
				for (size_t j = 0; j < pins_[i]->bus_.size(); j++) {
					pins_[i]->bus_[j]->times++;
				}
			}
		}*/
		return;
	}
	if (transit <= 0) {
		
		transit= nTransit.front();
		nTransit.pop_front();
		for (int i =0; i < npins; i++) {
			if (pin_width[i] ==1) {
				pins_[i]->net_->signal_ = pin_states[i].front() & 1;
				//std::cout << pins_[i]->net_->signal_;
				pins_[i]->net_->times++;
				int a = pins_[i]->net_->times;
				//if (a < 1000) {
					//pins_[i]->net_->signals_[a].push_back(pins_[i]->net_->signal_);
				//}
				pin_states[i].pop_front();
			}
			else {
				for (size_t j = 0; j < pins_[i]->bus_.size(); j++) {

					pins_[i]->bus_[j]->signal_ = pin_states[i].front() & 1;
					pins_[i]->bus_[j]->times++;
					int a = pins_[i]->bus_[j]->times;
					//std::cout << pins_[i]->bus_[j]->signal_;
					/*if (a < 1000) {
						pins_[i]->bus_[j]->signals_[a].push_back(pins_[i]->bus_[j]->signal_);
					}*/
					pin_states[i].front()=pin_states[i].front() >> 1;
				}
				pin_states[i].pop_front();
			}
		}
	} 
	/*else
	{
		for (int i = 0; i < npins; i++) {
			if (pin_width[i] == 1) {
				pins_[i]->net_->times++;
			}
			else {
				for (size_t j = 0; j < pins_[i]->bus_.size(); j++) {
					pins_[i]->bus_[j]->times++;
				}
			}
		}
		
	}*/
	transit--;
}

void  output::setup(std::string filename) {
	std::string file_name = filename + "." + name_ + ".evl_output";
	std::ofstream output_file(file_name.c_str());
	output_file <<pins_.size()<<std::endl;
	for (size_t i = 0; i < pins_.size(); i++) {
		if (pins_[i]->bus_.empty()) {
			output_file <<1<< std::endl;
		}
		else output_file << pins_[i]->bus_.size() << std::endl;
	}
	while (!result.empty()) {
		for (size_t i = 0; i < pins_.size(); i++) {
			output_file << result.front()<<" ";
		
			result.pop_front();
		}
		output_file << "" << std::endl;
	}

}

void output::compute_output() {
	std::string hex;
	std::string bin;
	for (size_t i = 0; i < pins_.size(); i++) {
		if (pins_[i]->bus_.empty()) 
		{
			//std::cout << pins_[i]->net_->name_ << std::endl;
			std::string hex;
			std::string bin;
			if (pins_[i]->net_->signal_==1) {
				hex = "1";
			}
			else
			{
				hex = "0";
			}
			result.push_back(hex);
		}
		else {
			for (int k = (pins_[i]->bus_.size())-1 ; k >= 0; k--) {
				//std::cout << pins_[i]->bus_[k]->name_ << std::endl;
				//std::cout << k << " ";
				if (pins_[i]->bus_[k]->signal_ == 1) {
					bin.append("1");
				}
				else bin.append("0");
			}
		
				for (size_t j = 0; j < pins_[i]->bus_.size(); ) {
					//std::cout << "" << std::endl;
					//std::cout << j << std::endl;
					for (size_t dig = 1; dig < 4; dig++) {
						if (bin.size() == (dig * 4)) {
							break;
						}
						if (bin.size() <(dig * 4))
						{
							
							int size = bin.size();
							for (size_t e = 0; e < (dig * 4) - size; e++)
							{
								bin = "0" + bin;
							}
							break;
						}
					}
					
					std::string tem = bin.substr(j,4);
			
					
					 if (tem=="0000") hex.append("0");
					else if (tem == "0001") hex.append("1");
					else if(tem == "0010") hex.append("2");
					else if  (tem == "0011") hex.append("3");
					else if (tem == "0100") hex.append("4");
					else if(tem == "0101") hex.append("5");
					else if (tem == "0110") hex.append("6");
					else if(tem == "0111")hex.append("7");
					else if(tem == "1000") hex.append("8");
					else if(tem == "1001") hex.append("9");
					else if(tem == "1010") hex.append("A");
					else if(tem == "1011") hex.append("B");
					else if (tem == "1100")hex.append("C");
					else if(tem == "1101") hex.append("D");
					else if(tem == "1110")hex.append("E");
					else if(tem == "1111") hex.append("F");
					//std::cout << hex << std::endl;
					j = j + 4;
					}
				result.push_back(hex);
			
				}
		//std::cout << hex << " ";
		
		hex = "";
			bin = "";
			}
	
		}

	
	





bool make_wires_table(const evl_wires &wires, evl_wires_table &wires_table) {
	for (evl_wires::const_iterator it = wires.begin(); it != wires.end(); ++it) {
		evl_wires_table::iterator same_name = wires_table.find(it->name);
		if (same_name != wires_table.end())
		{
			std::cerr << "Wire ¡¯" << it->name << "¡¯is already defined" << std::endl;
			return false;
		}
		wires_table.insert(std::make_pair(it->name, it->width));
	}
	return true;
}

std::string make_net_name(std::string wire_name, int i) { 
	assert(i >= 0); 
	std::ostringstream oss; 
	oss << wire_name << "[" << i << "]";
	return oss.str(); }

void netlist::create_net(std::string net_name) {
	assert(nets_table_.find(net_name) == nets_table_.end());
	
	net *n = new net(net_name);
	nets_table_[net_name] = n;
	nets_.push_back(n);
	
}



bool netlist::create_nets(const evl_wires &wires) {
	for (evl_wires::const_iterator it = wires.begin(); it != wires.end(); ++it){
		evl_wire tmp;
		if (it->width== 1) {
			
			create_net(it->name);
		}
 else
{
for (int i = 0; i < it->width; ++i) {
	std::string wire_name;
	wire_name = make_net_name(it->name, i);
 create_net(wire_name);
}
}
	}
	return true;
}

bool pin3::create(gate *g, size_t index, const evl_pin &p, const std::map<std::string, net *> &nets_table) {
	gate_ =g;
	index_ = index;         //store g and index; 
	
	if (p.msb == -1) { // a 1-bit wire 
		std::string net_name = p.name;
		std::map<std::string, net *>::const_iterator samename = nets_table.find(net_name);
	
		if (samename == nets_table.end()) {
			
			return false; } 
		net_ = samename->second;
		
		net_->append_pin(this); }
	else { // a bus ...
		if (p.lsb == -1) {
			std::string net_name = make_net_name(p.name,p.msb);
			std::map<std::string, net *>::const_iterator samename = nets_table.find(net_name);
			if (samename == nets_table.end()) {

				return false;
			}
			net_ = samename->second;
			
		
			net_->append_pin(this);
		}
		else
		{
			for (int i = p.lsb; i <=p.msb; i++)
			{
				
				std::string net_name = make_net_name(p.name, i);
				std::map<std::string, net *>::const_iterator samename = nets_table.find(net_name);
				if (samename == nets_table.end()) {

					return false;
				}
				net_ = samename->second;
              net_->append_pin(this);
			  bus_.push_back(net_);
			}
			std::map<std::string, net *>::const_iterator samename = nets_table.find(p.name);
			if (samename == nets_table.end()) {

				return false;
			}
			net_ = samename->second;

		}
	}



	return true;
	} 
void net::append_pin(pin3 *p) {
	connections_.push_back(p);
}




bool gate::create_pin( evl_pin &ep, size_t index, const std::map<std::string, net *> &nets_table, const evl_wires_table &wires_table) 
{ 
	//resolve semantics of ep using wires_table 
	if (ep.msb == -1) {
		evl_wires_table::const_iterator same_name = wires_table.find(ep.name);
		if (same_name == wires_table.end())
		{
			
			return false;
		}
		else
		{
			if (same_name->second > 1) {
				ep.msb = same_name->second;
				ep.lsb = 0;
			}
			else {
				ep.lsb = -1;
				ep.msb = -1;
			}
		}
	}
		pin3 *p = new pin3();
	pins_.push_back(p); 
	
	return p->create(this, index, ep, nets_table);
}





bool gate::create(evl_componet &c, const std::map<std::string, net *> &nets_table, const evl_wires_table &wires_table) {

	size_t index = 0; 
	for (pins::iterator it =c. pin2.begin(); it != c.pin2.end(); ++it) {
		create_pin(*it,index, nets_table, wires_table); 
	++index; } 
	return validate_structural_semantics()	;
}





bool netlist::create_gate( evl_componet &c, const evl_wires_table &wires_table) { 
	//gate *g = new gate; 
	if (c.type=="and")
	{
		and_gate *g = new and_gate(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	 else if (c.type == "evl_dff")
	{
		 flip_flop *g = new flip_flop(c.name);
		 gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	 else if (c.type == "or")
	 {
		 or_gate *g = new or_gate(c.name);
		 gates_.push_back(g);
		 return g->create(c, nets_table_, wires_table);
	 }
	
	 else if (c.type == "xor")
	 {
		 xor_gate *g = new xor_gate(c.name);
		 gates_.push_back(g);
		 return g->create(c, nets_table_, wires_table);
	 }
	else if (c.type == "not")
	{
		not_gate *g = new not_gate(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "buf")
	{
		buf_gate *g = new buf_gate(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "evl_one")
	{
		evl_one *g = new evl_one(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "evl_zero")
	 {
		evl_zero *g = new evl_zero(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "evl_input")
	{
		evl_input *g = new evl_input(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "evl_output")
	{
		output *g = new output(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "evl_lut") {
		evl_lut *g = new evl_lut(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "tris") {
		tris_gate *g = new tris_gate(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
	else if (c.type == "assign") {
		assign_ *g = new assign_(c.name);
		gates_.push_back(g);
		return g->create(c, nets_table_, wires_table);
	}
}



bool netlist::create_gates( evl_componets &comps, const evl_wires_table &wires_table) {
	for(evl_componets::const_iterator it = comps.begin(); it != comps.end(); ++it) {
		evl_componet c = *it;
		create_gate(c, wires_table); 
	} 
	return true;
}









bool netlist::create( const evl_wires &wires, evl_componets &comps,  const evl_wires_table &wires_table) { 
	return create_nets(wires) && create_gates(comps, wires_table);
}


void netlist::save(std::string file_name, std::string module_name) {
	std::ofstream output_file(file_name.c_str());
	if (!output_file)
	{
		std::cerr << "I can't write " << file_name.c_str() << ".netlist ." << std::endl;
	}
	output_file << "module" << " " << module_name <<  std::endl;
	if (nets_.size() > 0) {
		output_file << "nets" << " " << nets_.size() << std::endl;
		for (; !nets_.empty(); nets_.pop_front()) {
			output_file << "net"<<" "<<nets_.front()->name_<<" " <<nets_.front()->connections_.size() << std::endl;
			for (; !nets_.front()->connections_.empty(); nets_.front()->connections_.pop_front())
			{
				if (nets_.front()->connections_.front()->gate_->name_ == " ") {
					output_file << nets_.front()->connections_.front()->gate_->type_ << " " << nets_.front()->connections_.front()->index_ << std::endl;
				}
				else
				{
					output_file << nets_.front()->connections_.front()->gate_->type_ << " "<< nets_.front()->connections_.front()->gate_->name_ <<" " << nets_.front()->connections_.front()->index_ << std::endl;
				}
			}
		}
	}
	if (gates_.size() > 0)
	{
		output_file << "components" << " " << gates_.size() << std::endl;
		for (; !gates_.empty(); gates_.pop_front()) {
			if (gates_.front()->name_ == " ") {
				output_file << "component" << " " << gates_.front()->type_ <<" "<< gates_.front()->pins_.size()<<std::endl;
			}
			else
			{
				output_file << "component" << " " << gates_.front()->type_<< " "<< gates_.front()->name_<<" "<< gates_.front()->pins_.size() << std::endl;
			}
			for (size_t i = 0; i < gates_.front()->pins_.size(); i++)
			{
				if (gates_.front()->pins_[i]->bus_.empty()) {
					output_file << "pin 1" << " " << gates_.front()->pins_[i]->net_->name_ << std::endl;
				}
				else {
					output_file << "pin" << " " << gates_.front()->pins_[i]->bus_.size()<<" ";
					for (size_t j = 0; j < gates_.front()->pins_[i]->bus_.size(); j++)
					{
						output_file << gates_.front()->pins_[i]->bus_[j]->name_ << " ";
					}
					output_file << " " << std::endl;
				}
			}


		}

	}




}
int tris_gate::evaluate(const std::vector<int> &inputs) {
	pin3* pin_in = pins_[1];
	pin3* pin_en = pins_[2];
	int in = pin_in->net_->signal_;
	int en = pin_en->net_->signal_;

	if (en == 1) { 
		pins_[0]->out = in;
		return in; }
	else { 
		pins_[0]->out = 4;
		return 4; }
}


int buf_gate::evaluate(const std::vector<int> &inputs) {
	
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		if (inputs[i] == 1) {
			return 1;
		}
		else if  (inputs[i] == 0) {
			return 0;
		}
	} 
	return 4;
}


int not_gate::evaluate(const std::vector<int> &inputs) {
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		
		if (inputs[i] == 1)
		{
			
			return 0;
		}

		
	}return 1;
}



int xor_gate::evaluate(const std::vector<int> &inputs) {
	int onesnumber=0;
	
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		
		if (inputs[i]==1)
		{
			onesnumber = onesnumber + 1;
		}
		
	} 
	if (onesnumber % 2 == 0) {
		return 0;
		
	}
	else { return 1; }


}


int and_gate::evaluate(const std::vector<int> &inputs) {
	for (size_t i = 0; i < inputs.size(); ++i)
	{ 
		
		if (inputs[i]==0) 
		{
			return 0;
		}
	} return 1; 
}
int or_gate::evaluate(const std::vector<int> &inputs) {
	for (size_t i = 0; i < inputs.size(); ++i)
	{
		if (inputs[i] == 1)
		{
			return 1;
		}

		
	}return 0;
}





void flip_flop::compute_next_state() {
	
	net *input_net = pins_[1]->net_;
	next_state_ = input_net->signal_;
}
void flip_flop::compute_output() {
	state_ = next_state_;
	pins_[0]->net_->signal_ = state_;
	pins_[0]->net_->times++;
	pins_[0]->ptime++;
	int a = pins_[0]->net_->times;
	/*if (a < 1000) {
		pins_[0]->net_->signals_[a].push_back(pins_[0]->net_->signal_);
	}*/
	


}

void logic_gate::compute_output() {
	std::vector<int> inputs;  // retrieve logic values from all input nets 
	for (size_t i = 1; i < this->pins_.size(); i++) {
		int input = this->pins_[i]->net_->signal_;
		inputs.push_back(input);
	}
		int output = evaluate(inputs); 
		pins_[0]->net_->signal_ = output;
		pins_[0]->net_->times++;
		pins_[0]->ptime++;
		int a = pins_[0]->net_->times;
		/*if (a < 1000) {
			pins_[0]->net_->signals_[a].push_back(pins_[0]->net_->signal_);
		}*/
		
}

void evl_one::compute_output() {
	
	for (size_t i = 0; i < pins_.size(); i++) {
		pins_[i]->net_->signal_=1;
		pins_[i]->net_->times++;
		pins_[i]->ptime++;
		int a = pins_[i]->net_->times;
		/*if (a < 1000) {
			pins_[i]->net_->signals_[a].push_back(pins_[i]->net_->signal_);
		}*/
	}
	
}

void assign_::compute_output() {
	if (!pins_[0]->bus_.empty()) {
		for (int i = 0; i < pins_[0]->bus_.size();i++) {
			if (pins_[1]->bus_[i]->signal_ == 0) {
				pins_[0]->bus_[i]->signal_ = 0;
			}
			else if  (pins_[1]->bus_[i]->signal_ == 1) {
				pins_[0]->bus_[i]->signal_ = 1;
			}
			else if (pins_[1]->bus_[i]->signal_ == 4) {
				pins_[0]->bus_[i]->signal_ = 4;
			}
		}
		pins_[0]->ptime++;
	}
	else {
		if (pins_[1]->net_->signal_ == 0) {
			pins_[0]->net_->signal_ = 0;
		}
		else if (pins_[1]->net_->signal_ == 1) {
			pins_[0]->net_->signal_ = 1;
		}
		else if (pins_[1]->net_->signal_ == 4) {
			pins_[0]->net_->signal_ = 4;

		}
		pins_[0]->ptime++;
	}
		
}

void evl_zero::compute_output() {
	for (size_t i = 0; i <pins_.size(); i++) {
		pins_[i]->net_->signal_ = 0;
		pins_[i]->net_->times++;
		 pins_[i]->ptime++;
		 int a = pins_[i]->net_->times;
		 /*if (a < 1000) {
			 pins_[i]->net_->signals_[a].push_back(pins_[i]->net_->signal_);
		 }*/
	}
	
}

int net::decide(int a, int b) {
	if (a == 1 || b == 1) return 1;
	else if (a == 0 || b == 0)  return 0;
	else return 4;
}

void net::getvalue(int number) {
	std::vector<int>input;
	//std::cout << signals_.size();
		for (std::list<pin3 *>::iterator it = connections_.begin(); it != connections_.end(); ++it) {
		
			if ((*it)->dir_ == 'O') {
				if ((*it)->asout->type_ == "evl_input")
				{
					continue;
				}
				if ((*it)->ptime >= number) {
					continue;
				}
				
				if ((*it)->asout->sub == "logic") {
				for (size_t a = 1; a < (*it)->asout->pins_.size(); a++) {
			
							  (*it)->asout->pins_[a]->net_->getvalue(number);
							
						
					
					}
					
				}
				if ((*it)->asout->type_ == "evl_lut") {
					for (size_t b = 0; b < (*it)->asout->pins_[1]->bus_.size(); b++) {
						(*it)->asout->pins_[1]->bus_[b]->getvalue(number);
					}
				}
				if ((*it)->asout->type_ == "assign") {
					if (!(*it)->asout->pins_[1]->bus_.empty()) {
						for (size_t b = 0; b < (*it)->asout->pins_[1]->bus_.size(); b++) {
							(*it)->asout->pins_[1]->bus_[b]->getvalue(number);
						}
					}
					else { (*it)->asout->pins_[1]->net_->getvalue(number); }
				}
				if ((*it)->ptime < number) {
					(*it)->asout->compute_output();
					 input.push_back(signal_);
				  	continue;
				}
			}
		}
		//if (signals_.size() > 1) {
		/*if (number<signals_.size()){
			while (!signals_[number].empty()) {
				int tem = signals_[number].back();
					
				signal_ = decide(signal_, tem);
				signals_[number].pop_back();
			}
		}*/
		for (int i = 0; i < input.size(); i++) {
			if (input[i] == 1 || input[i] == 0) {
				signal_ = input[i];
				break;
			}
	 	}  
		/*if (name_ == "a[3]") {
			std::cout << "a[3]=" << signal_ << std::endl;
	}
		if (name_ == "a[2]") {
			std::cout << "a[2]=" << signal_ << std::endl;
		}
		if (name_ == "a[1]") {
			std::cout << "a[1]=" << signal_ << std::endl;
		}
		if (name_ == "a[0]") {
			std::cout << "a[0]=" << signal_ << std::endl;
		}*/
		return;
	
}
 




void netlist::simulate(std::string file_name, int cycles) {
	std::list<gate*> tmp;
	std::list<gate*> dff;
	std::list<gate*> logic;
	std::list<gate*>input;
	
	/*for (int i = 0; i <cycles; i++) {
		for (std::list<net *>::iterator st = nets_.begin(); st != nets_.end(); ++st)
		{
			std::list<int> start;
			(*st)->signals_.push_back(start);
		}
	}*/
	





	for (std::list<gate *>::iterator it = gates_.begin(); it != gates_.end(); ++it)
	{
		if ((*it)->type_ == "evl_input") {
			(*it)->setinput(file_name);
			input.push_back(*it);

		}
	if ((*it)->type_ == "evl_lut") {
			 (*it)->setinput(file_name);
			 
		}
		if ((*it)->type_ == "evl_output") {
			tmp.push_back(*it);
		}
		if ((*it)->type_ == "evl_dff") {
			dff.push_back(*it);
		}

	}
	for (std::list<net *>::iterator ap = nets_.begin(); ap != nets_.end(); ++ap)
	{
		  (*ap)->getvalue(0);
	}
	tmp.front()->compute_output();
	for (std::list<gate *>::iterator gd = dff.begin(); gd != dff.end(); ++gd) {

		(*gd)->compute_next_state();
	}

	for (int i = 1; i < cycles; i++)
	{
		if (!input.empty()) {
			input.front()->compute_output();
		}
		int a = i;
		for (std::list<net *>::iterator ap = nets_.begin(); ap != nets_.end(); ++ap)
		{
			(*ap)->getvalue(a);
		}
		tmp.front()->compute_output();

		/*for (std::list<gate *>::iterator ap = gates_.begin(); ap != gates_.end(); ++ap)
		{
			if ((*ap)->type_ != "evl_output") {
				if ((*ap)->sub == "logic") {
					for (size_t p = 1; p < (*ap)->pins_.size(); p++) {
						if ((*ap)->pins_[p]->net_->signal_ == 3) {
							(*ap)->visited = 2;
							logic.push_back(*ap);
							break;
						}
					}
					if ((*ap)->visited != 1) {

						continue;
					}
				}
				(*ap)->compute_output();
				// if ((*ap)->type_ == "buf") {
				// std::cout << " "<< (*ap)->pins_[0]->net_->signal_ << (*ap)-> type_<< " "<<(*ap)->pins_[1]->net_->signal_ <<" "  << std::endl;
				// }
			}
		}
		//std::cout << logic.size() << std::endl;
		for (std::list<gate *>::iterator ab = logic.begin(); ab != logic.end(); ++ab) {
		
			if ((*ab)->sub == "logic") {
				(*ab)->compute_output();

			}
		}*/
		
		
		for (std::list<gate *>::iterator gd = dff.begin(); gd != dff.end(); ++gd) {
			
			(*gd)->compute_next_state();
		}
	
	 }
	
	 tmp.front()->setup(file_name);
		  }
	


#endif

