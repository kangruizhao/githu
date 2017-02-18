package text;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
public class RadioButtonListener implements ActionListener {
	OptionDialogFrame x;
	RadioButtonListener(OptionDialogFrame a){
		x=a;
		
	}
	public void actionPerformed(ActionEvent e){

		if (e.getActionCommand().equals("English Student")){
			x.txtMidterm.setVisible(true);
			x.txtFinalExam.setVisible(true);
			x.txtResearch.setVisible(true);
			x.txtPresentation.setVisible(true);
			x.lblStudentTypes.setText("English Student");
			
}
	
		if (e.getActionCommand().equals("Math Student")){
			x.txtMidterm.setVisible(true);
			x.txtFinalExam.setVisible(true);
			x.txtResearch.setVisible(false);
			x.txtPresentation.setVisible(false);
			x.lblStudentTypes.setText("Math Student");
			
}
	
		if (e.getActionCommand().equals("Science Student")){
			x.txtMidterm.setVisible(true);
			x.txtFinalExam.setVisible(true);
			x.txtResearch.setVisible(true);
			x.txtPresentation.setVisible(false);
			x.lblStudentTypes.setText("Science Student");
		
}
}
}