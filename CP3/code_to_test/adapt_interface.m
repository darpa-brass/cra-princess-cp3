function [adapt_val, adapt_err] = adapt_interface(sensor_data, target_index, adapt_model)

%% input:
% a row of sensor reading
% a target index
% model

adapt_val = rand;
adapt_err = 0;