package com.cra.princess.simulation;

import java.util.ArrayList;
import java.util.List;

import org.apache.commons.cli.CommandLine;
import org.apache.commons.cli.CommandLineParser;
import org.apache.commons.cli.DefaultParser;
import org.apache.commons.cli.HelpFormatter;
import org.apache.commons.cli.Option;
import org.apache.commons.cli.Options;
import org.apache.commons.cli.ParseException;


public class CliParser {
    
    protected String base = "fixme.json";
    protected String vehicle;
    protected String world;
    protected String sensor;
    protected String output = "generated.json";
    protected double[] offsetEnu = new double[3];
    protected List<Perturbation> perturb;
    
    private Options options;
    
    CliParser(String[] args) {        
        options = getOptions();
        if (args.length == 0) {
            printHelp();
            System.exit(0);
        }
        CommandLineParser parser = new DefaultParser();
        CommandLine cmd;
        try {
            cmd = parser.parse(options,  args);
            if (cmd.hasOption("h")) {
                printHelp();
                System.exit(0);
            }
            if (cmd.hasOption("b"))
                base = cmd.getOptionValue("b");
            if (cmd.hasOption("v"))
                vehicle = cmd.getOptionValue("v");
            if (cmd.hasOption("w"))
                world = cmd.getOptionValue("w");
            if (cmd.hasOption("s"))
                sensor = cmd.getOptionValue("s");
            if (cmd.hasOption("o"))
                output = cmd.getOptionValue("o");            
            if (cmd.hasOption("P"))
                perturb = extractPerturbation(cmd);
            if (cmd.hasOption("i"))
                offsetEnu = getEnu(cmd.getOptionValue("i"));            
        } catch (ParseException e) {
            System.err.println(e.getLocalizedMessage());
            printHelp();
            System.exit(-1);
        }        
    }
    
    protected void testing() {
        if (perturb == null)
            return;
        for (Perturbation p : perturb)
            System.out.format("%s: %g, %g, %g m/s \n", p.tag, p.currentEnu[0], p.currentEnu[1], p.currentEnu[2]);
    }
    
    protected class Perturbation {
        final String tag;
        final double[] currentEnu;
        Perturbation(String tag_, double[] currentEnu_) {
            tag = tag_;
            currentEnu = currentEnu_;
        }
    }
    
    protected List<Perturbation> extractPerturbation(CommandLine cmd) {
        ArrayList<Perturbation> perturb = new ArrayList<Perturbation>();
        String[] raw = cmd.getOptionValues("P");
        // Must have an even number of entries
        if (raw == null || raw.length == 0 || raw.length % 2 == 1)
            return perturb;
        for (int i=0; i<raw.length; i+=2) {
            perturb.add(new Perturbation(raw[i], getEnu(raw[i+1])));
        }
        return perturb;
    }
    
    public void printHelp() {
        HelpFormatter formatter = new HelpFormatter();
        final String header = "Generate a JSON scenario from a set of templates plus specified perturbations."
                + "";
        final String footer = "" 
                + "Metron, Inc. 2016; Please send inquiries to gratton@metsci.com";
        formatter.printHelp(Main.appName, header, options, footer);
    }
    
    protected Options getOptions() {
        Options options = new Options();
        
        options.addOption("h", "Print this message");
        options.addOption(Option.builder("b").longOpt("base").hasArg()
                .argName("BASE").desc("Base JSON scenario to draw parameters from")
                .build());                
        options.addOption(Option.builder("v").longOpt("vehicle").hasArg()
                .argName("VEHICLE").desc("JSON scenario to draw vehicle parameters from. Overrides base.")
                .build());      
        options.addOption(Option.builder("s").longOpt("sensor").hasArg()
                .argName("SENSOR").desc("JSON scenario to draw sensor parameters from. Overrides base and vehicle.")
                .build());
        options.addOption(Option.builder("w").longOpt("world").hasArg()
                .argName("WORLD").desc("JSON scenario to draw world parameters from. Overrides base.")
                .build());
        options.addOption(Option.builder("i").longOpt("initial").hasArg()
                .argName("E,N,U").desc("Initial vehicle offset in meters (east, north, up) from coordinate origin. No spaces allowed.")
                .build());
        options.addOption(Option.builder("P").valueSeparator().hasArgs().argName("tag=vE,vN,vU")
                .desc("If tag is found in world data, set the current of that region to vE,vN,vU in m/s").build());
        options.addOption(Option.builder("o").longOpt("output").hasArg()
                .argName("OUTPUT").desc("File to output final JSON Scenario to.").build());
        return options;
    }
    
    public static double[] getEnu(String data) {
        double[] out = new double[3];
        String[] token = data.split(",");
        for (int i=0; i<token.length; i++)        
            out[i] = Double.valueOf(token[i]);
        return out;
    }
}
