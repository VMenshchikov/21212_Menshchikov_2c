package torrent.client.view;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.HexFormat;
import java.util.ResourceBundle;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.ProgressBar;
import javafx.scene.text.Text;
import javafx.stage.FileChooser;
import javafx.stage.Stage;
import javafx.util.Duration;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jetbrains.annotations.NotNull;
import torrent.client.controller.TorrentController;
import torrent.common.FileLoader;
import torrent.protocol.Parser;

public class TorrentView {
    //public TorrentView() {}

    @FXML
    private ResourceBundle resources;

    @FXML
    private URL location;

    @FXML
    private Button chooseFile;

    @FXML
    private Text countPiece;

    @FXML
    private Text fileLen;

    @FXML
    private Text fileHash;

    @FXML
    private Text nameFile;

    @FXML
    private Text nameTorrent;

    @FXML
    private ProgressBar progressBar;

    @FXML
    private Text pieceLen;

    @FXML
    private Button startLoad;

    File file;

    TorrentController controller;

    public void setController(TorrentController controller) { this.controller = controller; }

    @FXML
    void initialize() {
        chooseFile.setOnMouseClicked( e -> {
            FileChooser chooser = new FileChooser();
            chooser.setTitle("Select file");
            chooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("Torrent Files", "*.torrent"));
            file = chooser.showOpenDialog((Stage)chooseFile.getScene().getWindow());

            controller.setFile(file);
            Parser parser = controller.getParser();

            nameTorrent.setText(file.getName());
            nameFile.setText(parser.getName());
            fileLen.setText(parser.getLength().toString());
            countPiece.setText(Integer.toString(parser.getPiecesHash().size()));
            fileHash.setText(HexFormat.of().formatHex(parser.getFileHash()));
            pieceLen.setText(parser.getPieceLength().toString());
            progressBar.setProgress(controller.getProgress());
        });

        startLoad.setOnMouseClicked( e -> {
            if (controller.getParser() != null && !controller.isDownloading()) {
                updateProgress();
                controller.load();
            }
        });
    }

    private void updateProgress() {
        Timeline updateLine = new Timeline();
        KeyFrame update = new KeyFrame(Duration.millis(25), event -> {
            progressBar.setProgress(controller.getProgress());
            if (!controller.isDownloading()) updateLine.stop();
        });

        updateLine.getKeyFrames().add(update);
        updateLine.setCycleCount(Animation.INDEFINITE);
        updateLine.play();
    }

}
