package main;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.stage.Stage;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.nio.charset.StandardCharsets;

public class ChatClientController {

    private Stage stage;
    private OutputStream socketOutput;
    private InputStream socketInput;
    private Socket theSocket;
    ConnectionThread theConnection;

    @FXML
    private TextArea textfieldChat;

    @FXML
    private TextField textfieldMessage;

    @FXML
    private Button buttonSend;

    @FXML
    private Button buttonConnect;

    @FXML
    private Button buttonDisconnect;


    public ChatClientController() {
        // Create the new stage
        this.stage = new Stage();

        // Load the FXML file
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getClassLoader().getResource("ChatClient.fxml"));

            // Set this class as the controller
            loader.setController(this);

            // Load the scene
            this.stage.setScene(new Scene(loader.load()));

            // Setup the window/stage
            this.stage.setTitle("SE3313 - Project");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }


    void showStage() {
        this.stage.showAndWait();
    }


    @FXML
    void actionConnect(ActionEvent event) {
        try
        {
            theSocket = new Socket(InetAddress.getByName("35.162.177.130"),3001);
            socketOutput = theSocket.getOutputStream();
            socketInput = theSocket.getInputStream();
            theConnection = new ConnectionThread();
            theConnection.start();
            System.out.println("Connected");
        }
        catch(Exception ex)
        {
            System.out.println(ex.toString());
        }
    }

    @FXML
    void actionDisconnect(ActionEvent event) {
        try
        {
            sendString(" is disconnecting from server.");
            theSocket.close();
        }
        catch(Exception ex)
        {
            System.out.println(ex.toString());
        }
        System.out.println("disconnect");
    }

    @FXML
    void actionSend(ActionEvent event) {
        sendString(textfieldMessage.getText());
    }


    private void sendString(String s)
    {
        try
        {
            if (!s.isEmpty()) {
                socketOutput.write(s.getBytes());
                System.out.println("Sent:" + s);
            }
        }
        catch(Exception e)
        {
            System.out.println(e.toString());
        }
    }


    private class ConnectionThread extends Thread
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
                    String decoded = new String(readBuffer, StandardCharsets.UTF_8).trim();
                    System.out.println("Got:" + decoded);
                    textfieldChat.textProperty().setValue(textfieldChat.textProperty().get() + "\n" + decoded);
                }
            }
            catch (Exception e)
            {
                System.out.println(e.toString());
            }
        }
    }
}
