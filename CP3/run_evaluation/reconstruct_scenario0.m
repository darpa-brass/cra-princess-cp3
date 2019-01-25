#!/usr/bin/octave -qf
warning('off','all');
arg_list = argv ();

function reconstruct_scenario0(data_file_name, change_column_id, change_row_id, training_file_name1, training_file_name2, output_file_name)

change_column_id = str2num( change_column_id );
change_row_id = str2num( change_row_id );

% data: N*D
tr_data1 = dlmread(training_file_name1);
D = size(tr_data1,2);

rest_id = 1:D;
rest_id( change_column_id ) = [];

Y = tr_data1(:, change_column_id);

tr_data2 = dlmread(training_file_name2);

X = [tr_data1(:,rest_id), tr_data2 ];

degree = 2;
lambda = 1e-3;

all_data = dlmread(data_file_name);

X_te = all_data( change_row_id:end, [rest_id, change_column_id] );

pred = poly_ridge_reg(X', Y', X_te', degree, lambda);


all_data( change_row_id:end, change_column_id ) = pred';

dlmwrite(output_file_name, all_data);

endfunction

reconstruct_scenario0(arg_list{1},arg_list{2},arg_list{3},arg_list{4},arg_list{5},arg_list{6});