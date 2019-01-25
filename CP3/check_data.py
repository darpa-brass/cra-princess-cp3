import json
import sys

def check():
	sensor = json.load(open("/test/experiments.json"))[0]["perturbed_sensor"]
	try:
		j1 = json.load(open("/test/target_station_changed.json"))
		count = 0
		for items in j1:
			if items[sensor]!=None:
				count += 1
		if count < 500:
			return "Insufficient test data"
	except ValueError:
		return "Insufficient test data"
	try:
		j1 = json.load(open("/test/target_training_file.json"))
		count = 0
		for items in j1:
			if items[sensor]!=None:
				count += 1
		if count < 1000:
			return "Insufficient target training data"
	except ValueError:
		return "Insufficient target training data"
	try:
		j1 = json.load(open("/test/nearby_training_file.json"))
		count = 0
		for items in j1:
			if items[sensor]!=None:
				count += 1
		if count < 1000:
			return "Insufficient nearby training data"
	except ValueError:
		return "Insufficient nearby training data"
	return "Valid"

if __name__ == "__main__":
	sys.stdout.write(check())



