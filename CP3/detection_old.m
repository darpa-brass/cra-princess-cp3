function fail_info = detection(sensor_data, target_index, adapt_model)

%% do actual detection
adapt_info = adapt(sensor_data, target_index, adapt_model);

adapt_val = adapt_info(1);
adapt_err = adapt_info(2);

dev = abs( sensor_data(target_index) - adapt_val );
%disp( sensor_data(target_index) )
fail_conf = normcdf(dev, 0, adapt_err)*2-1;

fail_info(1) = fail_conf;
fail_info(2) = -1;