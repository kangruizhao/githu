package text;
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.util.*;
import javax.swing.*;
import javax.swing.border.*;
import javax.swing.JOptionPane;
import javax.swing.JOptionPane;
import javax.swing.JOptionPane;/**
 * @version 1.33 2007-04-28
 * @author Cay Horstmann
 */
public class TEXT1
{
   public static void main(String[] args)
   {
      EventQueue.invokeLater(new Runnable()
         {
            public void run()
            {
            	OptionDialogFrame frame = new OptionDialogFrame();
               frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
               frame.setVisible(true);
             
            }
         });
   }
}



class OptionDialogFrame extends JFrame{
   private 	JPanel buttonPanel;
   private ButtonGroup group;
  
   
   
   JLabel lblImage = new JLabel(new ImageIcon("AD1.png")); 
   JRadioButton radEnglish=new JRadioButton("English Student",true);
		 JRadioButton radMath=new JRadioButton("Math Student",false);
		 JRadioButton radScience=new JRadioButton("Science Student",false);
   JLabel lblMidterm=new JLabel("Midterm",JLabel.CENTER);
 	 JLabel lblFinalExam=new JLabel("Final Exam",JLabel.CENTER);
 	 JLabel lblResearch=new JLabel("Research",JLabel.CENTER);
 	 JLabel lblPresentation=new JLabel("Presentation",JLabel.CENTER);
 	 JLabel lblTypes=new JLabel("Student Types",JLabel.CENTER);
 	 JLabel lblGrades=new JLabel("Grades",JLabel.CENTER);
 	 JLabel lblStudentTypes=new JLabel("English Student",JLabel.CENTER);
    JLabel lblFinalGrade=new JLabel("",JLabel.CENTER);
    JTextField txtMidterm=new JTextField();
    JTextField txtFinalExam=new JTextField();
    JTextField txtResearch=new JTextField();
    JTextField txtPresentation=new JTextField();
    JButton ResetButton = new JButton("Reset");
    JButton CalculateButton = new JButton("Calculate Grade");
   RadioButtonListener rbListener=new RadioButtonListener(this);
  CalculateButtonListener cbListener=new CalculateButtonListener(this);
  ResetButtonListener resetListener=new ResetButtonListener(this);
   ImageIconListener  iiListener=new ImageIconListener(this);
   
   
   public OptionDialogFrame(){
   JPanel gridPanel=new JPanel();
   group=new ButtonGroup();
   gridPanel.setLayout(new GridLayout(2,3));
   buttonPanel=new JPanel();
   Border etched=BorderFactory.createEtchedBorder();
   Border titled=BorderFactory.createTitledBorder(etched,"Student types");
   buttonPanel.setBorder(titled);
   BoxLayout layout=new BoxLayout(buttonPanel, BoxLayout.Y_AXIS); 
   buttonPanel.setLayout(layout);
   gridPanel.add(buttonPanel);
	buttonPanel.add(radEnglish);
	buttonPanel.add(radMath);
	buttonPanel.add(radScience);
     
	
	
	
   group.add(radEnglish);
   group.add(radMath);
   group.add(radScience);
   add(gridPanel,BorderLayout.WEST);
   JPanel CalculatePanel = new JPanel();
 
   buttonPanel=new JPanel();
   
   
   
   CalculatePanel.add(CalculateButton);
  

  
   CalculatePanel.add(ResetButton);
   add(CalculatePanel,BorderLayout.SOUTH);
   pack();
   Container c=getContentPane();
   
   c.setLayout(null);

	c.add(txtMidterm);
	c.add(txtFinalExam);
	c.add(txtResearch);
	c.add(txtPresentation);
	c.add(lblImage);
	c.add(lblTypes);
	c.add(lblMidterm);
	c.add(lblFinalExam);
	c.add(lblResearch);
	c.add(lblPresentation);
	c.add(lblStudentTypes);
	c.add(lblGrades);
	c.add(lblFinalGrade);
	c.add(lblStudentTypes);
	radEnglish.addActionListener(rbListener);
	radMath.addActionListener(rbListener);
	radScience.addActionListener(rbListener);
	 CalculateButton.addActionListener(cbListener);
	 ResetButton.addActionListener(resetListener);
	 lblImage.addMouseListener(iiListener);
	 
	 txtMidterm.setBounds(400,50,50,40);
     txtFinalExam.setBounds(400,100,50,40);
     txtResearch.setBounds(400,150,50,40);
     txtPresentation.setBounds(400,200,50,40);
    
   lblGrades.setBounds(250, 0, 100, 40);
   lblStudentTypes.setBounds(350, 0, 200, 40);
   lblMidterm.setBounds(250, 50, 100, 40);
   lblFinalExam.setBounds(250, 100, 100, 40);
   lblResearch.setBounds(250, 150, 100, 40);
   lblPresentation.setBounds(250, 200, 100, 40);
   lblFinalGrade.setBounds(325, 250, 250, 40);
   lblImage.setBounds(0, 350, 500, 180);
   setTitle("Grade Calculator");
   setSize(600,600);
   setVisible(true);
   setResizable(false);
   }

  
}
