package game.view.startWindow;

import game.control.gameWindow.GameController;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.URL;
import java.util.*;
import java.util.regex.Pattern;

public class StartView {

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
        try (Scanner scanner = new Scanner(Objects.requireNonNull(getClass().getResourceAsStream("leaders.property")))) {
            HashMap<String, Integer> leaders = new HashMap<>();
            while (scanner.hasNextLine()) {
                var split = scanner.nextLine().split("=");
                if (leaders.containsKey(split[0]) && leaders.get(split[0]) < Integer.parseInt(split[1])) {
                    leaders.remove(split[0]);
                }
                leaders.put(split[0], Integer.parseInt(split[1]));
            }
            List<Map.Entry<String, Integer>> sortedLeaders = leaders.entrySet().stream()
                    .sorted(Map.Entry.comparingByValue(Comparator.reverseOrder())).toList();

            for (var a : sortedLeaders) {
                leadersTextArea.setText(leadersTextArea.getText() + "\n" + a.getKey() + " " + a.getValue());
            }
          /*  scanner.close();
            if (leaders.size() > 10) {
                System.out.println(leaders.size());

                try(FileWriter fw = new FileWriter(getClass().getResource("leaders.property").getPath(), false)) {
                    int count = 0;
                    for (var a : sortedLeaders) {
                        System.out.println(count);
                        fw.write(a.getKey() + "+" + a.getValue() + "\n");
                        count++;
                        if (count > 10) break;
                    }
                }
            }*/
        } /*catch (IOException ex) {
            throw new RuntimeException(ex.getMessage());
        }*/


        //newPlayerField.setText("111");

        pacmanImage.setOnMouseEntered(event -> {
            diagramImage.setVisible(true);
        });
        pacmanImage.setOnMouseExited(event -> {
            diagramImage.setVisible(false);
        });
/*        pacmanLeadersImage.setOnMouseEntered(event -> {
           leadersTextArea.setVisible(true);
        });
        pacmanLeadersImage.setOnMouseExited(event -> {
            leadersTextArea.setVisible(false);
        });*/

        playButton.setOnMouseClicked(event -> {
            try {
                String name = newPlayerField.getText();
                if (!Pattern.matches("[a-zA-Z0-9]{1,10}", name)) {/* return;*/ };

                GameController tmp = new GameController(name);
                tmp.getView().initialize((Stage) playButton.getScene().getWindow());
            } catch (IOException ex) {
                throw new RuntimeException(ex.getMessage());
            }
        });
    }

}
