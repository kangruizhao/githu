package text;
import javax.swing.JOptionPane;

import java.sql.*;

class EnglishStudent extends Student {
private final double ENGLISH_MIDTERM_PERCENTAGE=.25;
private final double ENGLISH_FINALEXAM_PERCENTAGE=.25;
private final double ENGLISH_RESEARCH_PERCENTAGE=.30;
private final double ENGLISH_PRESENTATION_PERCENTAGE=.20;

public static int i;
public EnglishStudent(){
System.out.println("EnglishStuden's constructor");
}


public void calculate(
	int midterm,int finalExamGrade,int research, int presentation){
	
	finalNumericGrade=(midterm*ENGLISH_MIDTERM_PERCENTAGE)+(finalExamGrade*ENGLISH_FINALEXAM_PERCENTAGE)
			+(research*ENGLISH_RESEARCH_PERCENTAGE)+(presentation*ENGLISH_PRESENTATION_PERCENTAGE);
	if (finalNumericGrade>=93)
		finalLetterGrade="A";
	else
		if((finalNumericGrade>=85)&(finalNumericGrade<93))
			finalLetterGrade="B";
		else
			if((finalNumericGrade>=78)&(finalNumericGrade<85))
				finalLetterGrade="C";
			else
				if((finalNumericGrade>=70)&(finalNumericGrade<78))
					finalLetterGrade="D";
				else
					if(finalNumericGrade<70)
						finalLetterGrade="F";
	
	try { 
        Class.forName("com.mysql.jdbc.Driver");     //¼ÓÔØMYSQL JDBCÇý¶¯³ÌÐò    
        //Class.forName("org.gjt.mm.mysql.Driver"); 
       System.out.println("Success loading Mysql Driver!"); 
     
      } 
      catch (Exception e) { 
        System.out.print("Error loading Mysql Driver!"); 
        e.printStackTrace(); 
      } 


	
	

	 try { 
	      Connection connect = DriverManager.getConnection( "jdbc:mysql://localhost:3306/test2","root","19930625"); 
	    
	      PreparedStatement Statement=connect.prepareStatement("INSERT INTO students VALUES(?,?,?,?,?,?,?)");
	      Statement.setString(1,"English student"+i);
	   
	      Statement.setDouble(2,midterm);
	      Statement.setDouble(3,finalExamGrade);
	      Statement.setDouble(4,research);
	      Statement.setDouble(5,presentation);
	      Statement.setDouble(6,finalNumericGrade);
	      Statement.setString(7,finalLetterGrade);
	      Statement.executeUpdate(); 
	      i++;
	  // } catch (ClassNotFoundException e) { 
	    // TODO Auto-generated catch block 
	   // System.out.println("An error has occurred:"+e.toString()); 
	  //  e.printStackTrace(); 
	   }catch(SQLException e) 
	   { 
	   } 
	 
}
public void calculate(){
}
}