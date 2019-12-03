package main;

import java.awt.*;
import java.awt.event.*;
import java.net.*;
import java.io.OutputStream;
import java.io.InputStream;
import java.lang.Thread;
import javax.swing.Action;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JButton;
import javax.swing.JPanel;

//import statements

public class Main extends JFrame {

    JLabel jlbHelloWorld;
    private OutputStream socketOutput;
    private InputStream socketInput;
    private Socket theSocket;
    public void SendString(String s)
    {
        try
        {
            socketOutput.write(s.getBytes());
            System.out.println("Sent:"+s);
        }
        catch(Exception e)
        {
            System.out.println(e.toString());
        }
    }

    public class UpButtonListener  implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            SendString("Up");
        }
    }
    public class RightButtonListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            SendString("Right");
        }
    }
    public class DownButtonListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            SendString("Down");
        }
    }
    public class LeftButtonListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            SendString("left");
        }
    }

    public class ConnectionThread extends Thread
    {
        public ConnectionThread()
        {

        }
        public void run()
        {
            try
            {
                byte[] readBuffer = new byte[256];
                for (int i=0;i<256;i++)
                    readBuffer[i]=0;
                while(true)
                {
                    socketInput.read(readBuffer);
                    String decoded = new String(readBuffer, "UTF-8");
                    System.out.println("Got:" + decoded);
                }
            }
            catch (Exception e)
            {
                System.out.println(e.toString());
            }
        }
    }
    ConnectionThread theConnection;
    public class ConnectButtonListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            String one = new String("hello");
            String two = new String("world");
            try
            {
                theSocket = new Socket(InetAddress.getByName("35.162.177.130"),3001);
                socketOutput = theSocket.getOutputStream();
                socketInput = theSocket.getInputStream();
                theConnection = new ConnectionThread();
                theConnection.start();
                System.out.println("connect");
            }
            catch(Exception ex)
            {
                System.out.println(ex.toString());
            }
        }
    }
    public class DisconnectButtonListener implements ActionListener
    {
        public void actionPerformed(ActionEvent e)
        {
            try
            {
                theSocket.close();
            }
            catch(Exception ex)
            {
                System.out.println(ex.toString());
            }
            System.out.println("disconnect");
        }
    }
    public class PlayingField extends Canvas
    {
        Dimension theDimension;
        Dimension minDim;
        public PlayingField (Dimension d)
        {
            theDimension = d;
            minDim = new Dimension();
            minDim.width = d.width/2;
            minDim.height = d.height/2;
        }
        public Dimension getPreferredSize()
        {
            return theDimension;
        }
        public Dimension getMinimumSize()
        {
            return minDim;
        }
        public void paint(Graphics g)
        {
            g.setColor(Color.black);
            Rectangle bounds= getBounds();
            g.fillRect(bounds.x,bounds.y,bounds.width,bounds.height);
        }
    }
    public static void main(String args[])
    {
//        new Main();
        ChatClientController chatClientController = new ChatClientController();
        chatClientController.showStage();
    }
    Main()
    {
        jlbHelloWorld = new JLabel("Hello World");
        JButton upButton = new JButton("Up");
        upButton.addActionListener(new UpButtonListener());
        upButton.setSize(100,20);
        JButton rightButton = new JButton("Right");
        rightButton.addActionListener(new RightButtonListener());
        rightButton.setSize(100,20);
        JButton downButton = new JButton("Down");
        downButton.addActionListener(new DownButtonListener());
        downButton.setSize(100,20);
        JButton leftButton = new JButton("Left");
        leftButton.addActionListener(new LeftButtonListener());
        leftButton.setSize(100,20);

        JPanel directionPanel = new JPanel(new GridBagLayout());
        GridBagConstraints c = new GridBagConstraints();
        c.gridx = 0; c.gridy = 1;
        directionPanel.add(upButton,c);
        c.gridx = 1; c.gridy = 0;
        directionPanel.add(rightButton,c);
        c.gridx = 1; c.gridy = 2;
        directionPanel.add(downButton,c);
        c.gridx = 2; c.gridy = 1;
        directionPanel.add(leftButton,c);

        JPanel connectionPanel = new JPanel(new GridBagLayout());
        JButton connectButton = new JButton("Connect");
        connectButton.addActionListener(new ConnectButtonListener());
        c.gridx = 0; c.gridy = 0;
        connectionPanel.add(connectButton,c);
        JButton disconnectButton = new JButton("Disconnect");
        disconnectButton.addActionListener(new DisconnectButtonListener());
        c.gridx = 1; c.gridy = 0;
        connectionPanel.add(disconnectButton,c);

        Rectangle theBounds = getBounds();
        Dimension d = new Dimension();
        d.width = 500;
        d.height = 450;
        PlayingField theField = new PlayingField(d);
        
        /*setLayout(new GridLayout(2,2));
        add(theField);
        add(connectionPanel);
        add(directionPanel);*/
        setLayout(new GridBagLayout());
        c.gridx = 0; c.gridy = 0;
        c.gridheight = 9;
        c.gridwidth = 10;
        c.weightx = 1.0;c.weighty=1.0;
        c.fill = GridBagConstraints.BOTH;
        add(theField,c);
        c.gridx = 0; c.gridy = 9;
        c.gridheight = 1;
        c.gridwidth = 2;
        c.fill = GridBagConstraints.NONE;
        add(connectionPanel,c);
        c.gridx = 7;c.gridy = 9;
        c.gridheight = 1;
        c.gridwidth = 2;
        c.fill = GridBagConstraints.NONE;
        add(directionPanel,c);
        this.setSize(500,500);
        this.setTitle("Network Game Console");

        setVisible(true);
    }
}