package com.cra.princess.metron.viewer.capture;

import com.cra.princess.metron.viewer.controller.RemusViewerController;
import org.apache.log4j.Logger;

import java.io.File;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.channels.SeekableByteChannel;
import java.nio.file.Files;
import java.nio.file.OpenOption;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import static java.nio.file.StandardOpenOption.APPEND;
import static java.nio.file.StandardOpenOption.CREATE;

/**
 * Base class for writing incoming messages on a specific JMS topic to a JMS Test Harness map message data file<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Dec 18, 2017<br>
 * <br>
 * Copyright 2017 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public abstract class MessageWriter extends Thread {
    private static Logger LOG = Logger.getLogger(MessageWriter.class.getName());

    private static final String CAPTURE_DIRECTORY = "remusCaptures";
    private static final String CAPTURE_FILE_EXT = ".jth";

    private boolean doWork = true;
    private SeekableByteChannel sbc = null;

    protected RemusViewerController controller = null;

    public MessageWriter(RemusViewerController controller) {
        super();

        if (controller == null) {
            String msg = "No controller provided";
            LOG.error(msg);
            throw new IllegalArgumentException(msg);
        }

        this.controller = controller;
    }

    public void run() {
        while (doWork) {
            try {
                Thread.sleep(100);
            }
            catch(InterruptedException e) {
                // Ignore
            }
        }
    }

    public void stopCapture() {
        if (this.sbc != null && this.sbc.isOpen()) {
            try {
                this.sbc.close();
            } catch (IOException e) {
                LOG.error(e.getMessage(), e);
            }
        }

        this.doWork = false;
    }

    protected void setCaptureFile(String captureFileBaseName) {
        Date now = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("ddMMMyyyy-HHmm");
        String fileTs = sdf.format(now);

        String captureDir = ".\\" + CAPTURE_DIRECTORY + "-" + fileTs + "\\";
        File captureDirFile = new File(captureDir);
        if (captureDirFile.exists() == false) {
            captureDirFile.mkdir();
        }

        String captureFileName = captureDir + captureFileBaseName + CAPTURE_FILE_EXT;
        File captureFile = new File(captureFileName);
        if (captureFile.exists() == false) {
            try {
                captureFile.createNewFile();
            } catch (IOException e) {
                LOG.error(e.getMessage(), e);
            }
        }

        Path capturePath = Paths.get(captureFileName);

        // Create the set of options for appending to the file.
        Set<OpenOption> options = new HashSet<OpenOption>();
        options.add(APPEND);
        options.add(CREATE);

        try {
            this.sbc = Files.newByteChannel(capturePath, options);
        } catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    protected void writeTopicMessage(String timestamp, String content, String topicName) {
        LOG.debug("Writing message to: " + topicName);
        StringBuffer sb = new StringBuffer();
        sb.append(timestamp);
        sb.append("\t");
        sb.append(content);
        sb.append("\t");
        sb.append("DEST=" + topicName + "&SRC=RemusViewer");
        sb.append("\n");

        // Convert the file entry to a ByteBuffer
        ByteBuffer bb = ByteBuffer.wrap(sb.toString().getBytes());

        try  {
            if (this.sbc.isOpen()) {
                this.sbc.write(bb);
            }
        } catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }
}
