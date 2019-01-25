function adapt_model = train_adapter_interface(sensor_data, target_index)

%% Input: 
% sensor_data: a set of rows of sensor readings (a matrix)
% target_index: index of the target sensor that we want to reconstruct

%% Output:
% adapt_model: a structure

%%disp(sensor_data);
%%disp(target_index);

N_sensor = size(sensor_data, 2);
X = sensor_data(:, target_index);
Y = sensor_data(:, [1:target_index-1,target_index+1:N_sensor]);

d = 2;
lambda = 1e-2;

[weight, min_val, max_val] = train_ridge_reg(X', Y', d, lambda);

adapt_model.weight = weight;
adapt_model.minv = min_val;
adapt_model.maxv = max_val;
