package game.startWindow;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import javafx.scene.layout.Pane;

public class StartController {

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private ImageView diagramImage;

    @FXML
    private TextArea leadersTextArea;

    @FXML
    private TextField newPlayerField;

    @FXML
    private ImageView pacmanImage;

    @FXML
    private ImageView pacmanLeadersImage;

    @FXML
    private Button playButton;

    @FXML
    private ChoiceBox<?> selectPlayerBox;

    @FXML
    void initialize() {
        assert diagramImage != null : "fx:id=\"DiagramImage\" was not injected: check your FXML file 'Start.fxml'.";
        assert leadersTextArea != null : "fx:id=\"LeadersTextArea\" was not injected: check your FXML file 'Start.fxml'.";
        assert newPlayerField != null : "fx:id=\"NewPlayerField\" was not injected: check your FXML file 'Start.fxml'.";
        assert pacmanImage != null : "fx:id=\"PacmanImage\" was not injected: check your FXML file 'Start.fxml'.";
        assert pacmanLeadersImage != null : "fx:id=\"PacmanLeadersImage\" was not injected: check your FXML file 'Start.fxml'.";
        assert playButton != null : "fx:id=\"PlayButton\" was not injected: check your FXML file 'Start.fxml'.";
        assert selectPlayerBox != null : "fx:id=\"SelectPlayerBox\" was not injected: check your FXML file 'Start.fxml'.";


        pacmanImage.setOnMouseEntered(event -> {
            diagramImage.setVisible(true);
        });
        pacmanImage.setOnMouseExited(event -> {
            diagramImage.setVisible(false);
        });
        pacmanLeadersImage.setOnMouseEntered(event -> {
           leadersTextArea.setVisible(true);
        });
        pacmanLeadersImage.setOnMouseExited(event -> {
            leadersTextArea.setVisible(false);
        });

        playButton.setOnMouseClicked(event -> {
            try {
                FXMLLoader fxmlLoader = new FXMLLoader(StartWindow.class.getResource("Game.fxml"));
                Stage stage = (Stage) playButton.getScene().getWindow();
                stage.setScene(new Scene(fxmlLoader.load()));
            } catch(IOException ex) {
                Stage errStage = new Stage();
                Pane pane = new Pane();
                Button button = new Button("OK");
                pane.getChildren().add(button);
                scene.getRoot().
                errStage.setTitle("Error");
                errStage.setScene(scene);
            }
        });
    }

}
