package text;
import java.awt.*;
import java.io.File;
import javax.swing.*;
import java.awt.event.*;
public class ImageIconListener  implements MouseListener{
	OptionDialogFrame x;
	ImageIconListener(OptionDialogFrame a){
		x=a;
	}
	public void mouseClicked(MouseEvent e){try { 
	  
	    String url = "http://hs.blizzard.cn/landing"; 
	    java.net.URI uri = java.net.URI.create(url); 
	    // ��ȡ��ǰϵͳ������չ 
	    java.awt.Desktop dp = java.awt.Desktop.getDesktop(); 
	    // �ж�ϵͳ�����Ƿ�֧��Ҫִ�еĹ��� 
	    if (dp.isSupported(java.awt.Desktop.Action.BROWSE)) { 
	   
	      dp.browse(uri);// ��ȡϵͳĬ������������� 
	
	    } 
	   } catch (java.lang.NullPointerException e1) { 
	    // ��ΪuriΪ��ʱ�׳��쳣 
	    e1.printStackTrace(); 
	   } catch (java.io.IOException e1) { 
	    // ��Ϊ�޷���ȡϵͳĬ������� 
	    e1.printStackTrace(); 
	   } 
	
	
}

	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public void mousePressed(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
	
	public void mouseReleased(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}
}