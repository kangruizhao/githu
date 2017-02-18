package text;
import java.awt.*;
import javax.swing.JOptionPane;
import java.sql.*;
import java.awt.event.*;
import javax.swing.*;
public class CalculateButtonListener implements ActionListener {

	OptionDialogFrame x;
	CalculateButtonListener(OptionDialogFrame a){
		x=a;
	}
	public void actionPerformed(ActionEvent e){

	if (x.lblStudentTypes.getText()=="English Student"){
	try{
		int b=Integer.parseInt(x.txtMidterm.getText());
		int c=Integer.parseInt(x.txtFinalExam.getText());
		int d=Integer.parseInt(x.txtPresentation.getText());
		int g=Integer.parseInt(x.txtResearch.getText());
		if (b>100||b<0||c>100||c<0||d>100||d<0||g>100||g<0)throw new InvalidgradeException();
	EnglishStudent eStudent=new EnglishStudent();
	eStudent.calculate(Integer.parseInt(x.txtMidterm.getText()),Integer.parseInt(x.txtFinalExam.getText()),
			Integer.parseInt(x.txtResearch.getText()),
			Integer.parseInt(x.txtPresentation.getText()));
	x.lblFinalGrade.setText("Numeric Grade:"+eStudent.getFinalNumericGrade()+"   Letter Grade:"+eStudent.getFinalLetterGrade());
	}
	catch(java.lang.NumberFormatException e1){
		JOptionPane.showMessageDialog(null, "you should enter valid grade");
	}
	catch(Exception e1){
		JOptionPane.showMessageDialog(null, "you1 should enter valid grade");
	}
}
	
	if (x.lblStudentTypes.getText()=="Math Student"){
try{
	
	int b=Integer.parseInt(x.txtMidterm.getText());
	int c=Integer.parseInt(x.txtFinalExam.getText());
	if (b>100||b<0||c>100||c<0)throw new InvalidgradeException();
	MathStudent mStudent=new MathStudent();
	mStudent.calculate(Integer.parseInt(x.txtMidterm.getText()),Integer.parseInt(x.txtFinalExam.getText()));
	x.lblFinalGrade.setText("Numeric Grade:"+mStudent.getFinalNumericGrade()+"   Letter Grade:"+mStudent.getFinalLetterGrade());
	}
catch(java.lang.NumberFormatException e1){
	JOptionPane.showMessageDialog(null, "you should enter valid grade");
}
catch(Exception e1){
		JOptionPane.showMessageDialog(null, "you1 should enter valid grade");
	}

	}


	
	if (x.lblStudentTypes.getText()=="Science Student"){
try{
	int b=Integer.parseInt(x.txtMidterm.getText());
	int c=Integer.parseInt(x.txtFinalExam.getText());

	int g=Integer.parseInt(x.txtResearch.getText());
	if (b>100||b<0||c>100||c<0|g>100||g<0)throw new InvalidgradeException();
	ScienceStudent sStudent=new ScienceStudent();
	sStudent.calculate(Integer.parseInt(x.txtMidterm.getText()),Integer.parseInt(x.txtFinalExam.getText()),
			Integer.parseInt(x.txtResearch.getText()));
	x.lblFinalGrade.setText("Numeric Grade:"+sStudent.getFinalNumericGrade()+"   Letter Grade:"+sStudent.getFinalLetterGrade());
	
	}catch(java.lang.NumberFormatException e1){
		JOptionPane.showMessageDialog(null, "you should enter valid grade");
	}
	catch(Exception e1){
			JOptionPane.showMessageDialog(null, "you1 should enter valid grade");
		}

	
	 
	 
	 
	 
	}
	
	


	
	}
}
