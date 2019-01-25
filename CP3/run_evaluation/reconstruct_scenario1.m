#!/usr/bin/octave -qf
warning('off','all');
arg_list = argv ();

function reconstruct_scenario1(data_file_name, change_column_id, change_row_id, eval_start_row_id, output_file_name)

change_column_id = str2num( change_column_id );
change_row_id = str2num( change_row_id );
eval_start_row_id = str2num( eval_start_row_id );

% data: N*D
data = dlmread(data_file_name);
D = size(data,2);

rest_id = 1:D;
rest_id( change_column_id ) = [];

restX = data(1:change_row_id-1, rest_id);
missX = data(1:change_row_id-1, change_column_id);


rand('seed',2017);
rdp = randperm( change_row_id-1 );
sel_pts = rdp(1: min(5000,length(rdp)));
restX = restX(sel_pts,:);
missX = missX(sel_pts,:);

degree = 2;
lambda = 1e-3;

restX_te = data(change_row_id:eval_start_row_id-1, rest_id);
newX_te = data(change_row_id:eval_start_row_id-1, change_column_id);
%missX_pred = poly_ridge_reg(restX', missX', restX_te', degree, lambda);

% estimate missX te by iterative local search
N_tr = size(restX,1);
N_te = size(restX_te,1);
n_block = 2000;
batch = floor(N_te/n_block);
sort_id = [];
for i = 1:batch+1
    upper = min(n_block*i,N_te);
    dist = L2_distance(restX_te( n_block*(i-1)+1:upper,: )', restX', eye( length(rest_id) ));
    [sort_dist, sort_sub_id] = sort(dist,2);
    sort_id = [sort_id; sort_sub_id];
end

N_local_pt = max(50, 3*N_tr/N_te);
select_id = sort_id(:,1:N_local_pt);
select_id = unique(select_id);

missX_pred = poly_ridge_reg( restX(select_id,:)', missX(select_id)', restX_te', degree, lambda);

restX_eval = data(eval_start_row_id:end, rest_id);
newX_eval = data(eval_start_row_id:end, change_column_id);

% train a new model
pred = poly_ridge_reg( [restX_te,newX_te]', missX_pred, [restX_eval,newX_eval]', degree, lambda);

data( eval_start_row_id:end, change_column_id ) = pred';
dlmwrite(output_file_name, data);
endfunction

reconstruct_scenario1(arg_list{1},arg_list{2},arg_list{3},arg_list{4},arg_list{5});