module torrent {
    requires javafx.controls;
    requires javafx.fxml;

    requires bencode;
    requires org.jetbrains.annotations;

    requires org.apache.logging.log4j;

    exports torrent;
    exports torrent.common;
    exports torrent.client.model;
    exports torrent.client.controller;
    exports torrent.client.view;


    exports torrent.protocol;

    opens torrent.client.view to javafx.fxml;

}
