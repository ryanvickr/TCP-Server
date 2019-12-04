package main;

import javafx.application.Application;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) throws Exception {
        //TODO: Implement this!
        new ChatClientController().showStage();
    }


    public static void main(String[] args) {
        launch(args);
    }
}
