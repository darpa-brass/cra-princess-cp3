package com.cra.princess.metron.viewer.csv;

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
 * Base class for writing data in comma-separated values format<br>
 * <br>
 * Created By: Michael Reposa (mreposa@cra.com)<br>
 * Creation Date: Jul 16, 2018<br>
 * <br>
 * Copyright 2018 Charles River Analytics, Inc.<br>
 * See http://www.cra.com for information.
 */

public class CsvWriter {
    private static Logger LOG = Logger.getLogger(CsvWriter.class.getName());

    private static final String CSV_DIRECTORY = "remusCsv";
    private static final String CSV_FILE_EXT = ".csv";

    private SeekableByteChannel sbc = null;

    public CsvWriter(String fileBaseName) {
        setCsvFileName(fileBaseName);
    }

    private void setCsvFileName(String fileBaseName) {
        if (fileBaseName == null || fileBaseName.isEmpty()) {
            throw new IllegalArgumentException("Requires a base filename (no path or extension)");
        }

        // Get a timestamp so we get a unique directory name each time
        Date now = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("ddMMMyyyy-HHmm");
        String fileTs = sdf.format(now);

        // Create the CSV directory if it doesn't exist
        String captureDir = "." + File.separator + CSV_DIRECTORY + "-" + fileTs + File.separator;
        File captureDirFile = new File(captureDir);
        if (captureDirFile.exists() == false) {
            captureDirFile.mkdir();
        }

        // Create the new CSV file
        String captureFileName = captureDir + fileBaseName + CSV_FILE_EXT;
        File captureFile = new File(captureFileName);
        if (captureFile.exists() == false) {
            try {
                captureFile.createNewFile();
            } catch (IOException e) {
                LOG.error(e.getMessage(), e);
            }
        }

        Path capturePath = Paths.get(captureFileName);

        // Create the set of options for appending to the CSV file
        Set<OpenOption> options = new HashSet<OpenOption>();
        options.add(APPEND);
        options.add(CREATE);

        // Create a SeekableByteChannel to the CSV file
        try {
            this.sbc = Files.newByteChannel(capturePath, options);
        } catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    public void close() {
        try {
            this.sbc.close();
        } catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }

    /**
     * Record a surge velocity value in the CSV file
     *
     * @param timestamp the time at which the velocity value was reported
     * @param surgeVelocity the surge velocity to record, in meters per second
     */
    public void appendSurgeValue(Long timestamp, Double surgeVelocity) {
        StringBuffer sb = new StringBuffer();
        sb.append(Long.toString(timestamp));
        sb.append(",");
        sb.append(Double.toString(surgeVelocity));
        sb.append("\n");

        // Convert the file entry to a ByteBuffer
        ByteBuffer bb = ByteBuffer.wrap(sb.toString().getBytes());

        try  {
            if (this.sbc != null && this.sbc.isOpen()) {
                this.sbc.write(bb);
            }
        } catch (IOException e) {
            LOG.error(e.getMessage(), e);
        }
    }
}
