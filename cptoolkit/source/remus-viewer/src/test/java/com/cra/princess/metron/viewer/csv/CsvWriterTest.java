package com.cra.princess.metron.viewer.csv;

import org.junit.Test;

import java.util.Date;

/**
 * Tests for the CsvWriter class.
 * 
 */
public class CsvWriterTest {
	@Test
    public void writeTest() {
		// Creation
		CsvWriter csvWriter = new CsvWriter("groundTruthSurge");

		assert(csvWriter != null);

		csvWriter.appendSurgeValue(new Date().getTime(), 2.0);
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			// no-op
		}
		csvWriter.appendSurgeValue(new Date().getTime(), 2.2);
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			// no-op
		}
		csvWriter.appendSurgeValue(new Date().getTime(), 2.6);
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			// no-op
		}
		csvWriter.appendSurgeValue(new Date().getTime(), 2.8);
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			// no-op
		}
		csvWriter.appendSurgeValue(new Date().getTime(), 3.0);
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			// no-op
		}
		csvWriter.appendSurgeValue(new Date().getTime(), 3.2);
		try {
			Thread.sleep(1000);
		}
		catch (InterruptedException e) {
			// no-op
		}

		csvWriter.close();
	}
}
