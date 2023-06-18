package torrent;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.jetbrains.annotations.NotNull;
import torrent.client.controller.TorrentController;
import torrent.client.view.TorrentView;

import java.io.IOException;
import java.util.Arrays;

public class Torrent extends Application {
    private final static Logger logger = LogManager.getLogger(Torrent.class);
    static int port = -1;
    static final int defaultPort = 11111;
    public static void main(String[] args) {
        try {
            if (args.length != 1) {
                logger.fatal("Args != port or \"standard\"");
                return;
            }
            if (args[0].equals("standard")) { port = defaultPort; }
            else {
                port = Integer.parseInt(args[0]);
                if (port < 1024 || port > 49151) {
                    logger.fatal("Please, use port 1024-49151 or \"standard\" for start with \"non test in local loop\" mode"); //ну.....
                    return;
                }
            }
        } catch (NumberFormatException ex) {
            logger.fatal("Arg not int(port for server)");
            return;
        }

        //for tests
        {
            if (port != 1701 && port != 1702 && port != 1703 && !args[0].equals("standard")) {
                logger.fatal("Not test port. Change port or use 1701, 1702, 1703 ports for local loop.");
                return;
            }
        }


        try {
            launch(args);
        } catch (Error | Exception error) {
            error.printStackTrace();
            System.out.println(error.getMessage());
            System.out.flush();
        }

    }

    @Override
    public void start(@NotNull Stage primaryStage) {
        try {
            // Загрузка FXML-файла
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/torrent/client/view/view.fxml"));
            Scene scene = new Scene(loader.load());

            primaryStage.setTitle("Torrent");
            primaryStage.setScene(scene);
            primaryStage.setResizable(false);

            TorrentView view = loader.getController();
            TorrentController controller = new TorrentController(view, port, port==defaultPort);
            controller.createClient();
            view.setController(controller);

            primaryStage.setOnCloseRequest( event -> {
                controller.endProgram();
            });

            primaryStage.show();
        } catch (IOException ex) {
            logger.fatal("Cant create view: " + ex.getMessage());
        }
    }
}

