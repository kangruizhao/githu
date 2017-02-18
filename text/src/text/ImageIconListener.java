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
	    // 获取当前系统桌面扩展 
	    java.awt.Desktop dp = java.awt.Desktop.getDesktop(); 
	    // 判断系统桌面是否支持要执行的功能 
	    if (dp.isSupported(java.awt.Desktop.Action.BROWSE)) { 
	   
	      dp.browse(uri);// 获取系统默认浏览器打开链接 
	
	    } 
	   } catch (java.lang.NullPointerException e1) { 
	    // 此为uri为空时抛出异常 
	    e1.printStackTrace(); 
	   } catch (java.io.IOException e1) { 
	    // 此为无法获取系统默认浏览器 
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