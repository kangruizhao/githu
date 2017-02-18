package text;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class ResetButtonListener implements ActionListener {
	OptionDialogFrame x;
	ResetButtonListener(OptionDialogFrame a){
		x=a;
		
	}
	public void actionPerformed(ActionEvent e){
		x.radEnglish.doClick();
		x.txtMidterm.setVisible(true);
		x.txtFinalExam.setVisible(true);
		x.txtResearch.setVisible(true);
		x.txtPresentation.setVisible(true);
		x.txtMidterm.setText("");
		x.txtFinalExam.setText("");
		x.txtResearch.setText("");
		x.txtResearch.setText("");
		x.txtPresentation.setText("");
		x.lblStudentTypes.setText("English Student");
		x.lblFinalGrade.setText("");
}
}