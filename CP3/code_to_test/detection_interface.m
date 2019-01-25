function [fail_conf, fail_type] = detection_interface(sensor_data)

%% input: a row of sensor reading

N_window = size(sensor_data,1);
N_sensor = size(sensor_data,2);

%% do actual detection
%% ...

fail_conf = rand(1, N_sensor);
fail_type = ones(1, N_sensor);