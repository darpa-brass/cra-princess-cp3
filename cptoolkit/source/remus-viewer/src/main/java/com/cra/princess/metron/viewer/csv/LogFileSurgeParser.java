package com.cra.princess.metron.viewer.csv;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class LogFileSurgeParser {
    public static void main(String[] args) {
        int status = 0;
        int lineNum = 1;

        CsvWriter rawCsvWriter = new CsvWriter("rawDvlSurge");
        CsvWriter transformedCsvWriter = new CsvWriter("transformedDvlSurge");

        if (args != null && args.length > 0) {
            String file = args[0];
            Path path = Paths.get(file);
            try(BufferedReader reader = Files.newBufferedReader(path, Charset.forName("UTF-8"))) {
                String line = null;
                Long timestamp = 0L;
                Double surge = 0.0;
                while((line = reader.readLine()) != null) {
                    if (line.indexOf("DVL raw - ") != -1) {
                        // Parse raw DVL values
                        // Example:
                        // DVL raw - 1533152505687: depth(12.2942048154944780), vE(-0.0159019518544808), vN(3.2406522198865420), vU(0.0151968826600305), roll(-0.0698687975955694), pitch(-0.0795185398427249), heading(-0.2985398666156782), surge(3.2406668738092500), sway(0.0010076332566118), heave(-0.0196932790956603)
                        int ts_start = line.indexOf("DVL raw - ") + 10;
                        int ts_end = line.indexOf(": ");
                        timestamp = Long.parseLong(line.substring(ts_start, ts_end));
                        int surge_start = line.indexOf("surge(") + 6;
                        int surge_end = line.indexOf("), sway");
                        surge = Double.parseDouble(line.substring(surge_start, surge_end));
                        rawCsvWriter.appendSurgeValue(timestamp, surge);
                        System.out.println("Line " + lineNum + ": Raw DVL: " + timestamp + " " + surge);
                    }
                    else if (line.indexOf("Read bytes: {\"swayConf\":") != -1) {
                        // Parse transformed DVL values
                        // Example:
                        // Read bytes: {"swayConf": 1, "surgeStdDev": 0, "heaveConf": 1, "heaveStdDev": 0, "pitch": 0, "heave": 0, "vE": 0, "altitude": 90, "vUStdDev": 0, "vNStdDev": 0, "vN": 3.2, "vU": 0, "vEConf": 1, "sway": 0, "roll": 0, "swayStdDev": 0, "timestamp": 1533152504687, "vUConf": 1, "surgeConf": 1, "vNConf": 1, "vEStdDev": 0, "surge": 3.2, "depth": 10, "heading": 0}
                        int ts_start = line.indexOf("\"timestamp\": ") + 13;
                        int ts_end = line.indexOf(", \"vUConf\":");
                        timestamp = Long.parseLong(line.substring(ts_start, ts_end));
                        int surge_start = line.indexOf("\"surge\": ") + 9;
                        int surge_end = line.indexOf(", \"depth\":");
                        surge = Double.parseDouble(line.substring(surge_start, surge_end));
                        transformedCsvWriter.appendSurgeValue(timestamp, surge);
                        System.out.println("Line " + lineNum + ": Transformed DVL: " + timestamp + " " + surge);
                    }

                    lineNum++;
                }
            }
            catch(IOException e) {
                e.printStackTrace();
            }
        }
        else {
            System.out.println("No log file provided");
            status = -1;
        }

        System.exit(status);
    }
}
