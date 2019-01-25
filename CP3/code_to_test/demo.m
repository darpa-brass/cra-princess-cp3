%% load data
% each row is a sample
% each column is a sensor
sensor_data = dlmread('simulator_data_test.txt');  % use python to generate the matrix

% use 2000 samples to train
target_index = 3;
input_matrix = sensor_data(1:2000,:);

%% Train the model
adapt_model = train_adapter_interface(input_matrix, target_index);

% test on 20 new samples one by one
for i = 2001:2020
    
    [fail_conf, fail_type] = detection_interface(sensor_data(i,:));
    [adapt_val, adapt_err] = adapt_interface(sensor_data(i,:), 3, []);
    
    fprintf('index %d , confidence: %.3f , failure type: %d ', i, fail_conf(3), fail_type(3));
    fprintf('adapt value %.3f , adapt err %.3f\n', adapt_val, adapt_err);
end
