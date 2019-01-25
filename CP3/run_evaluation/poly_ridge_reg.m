function pred = poly_ridge_reg(X, Y, X_te, d, lambda)

%% removing bad points
all_train_data = [X; Y];
bad_idx = find( min( all_train_data ) < -90 );
X(:,bad_idx) = [];
Y(:,bad_idx) = [];

D = size(X,1);
for d = 1:D
    fix_idx{d} = find( X_te(d,:) < -90 );
end

%% scaling data
min_val = min(X,[],2);
max_val = max(X,[],2);


X = (X - repmat(min_val,1,size(X,2)) ) ./ repmat( max_val-min_val+0.1, 1, size(X,2) );
X_te = (X_te - repmat(min_val,1,size(X_te,2)) ) ./ repmat( max_val-min_val+0.1, 1, size(X_te,2) );

mean_val = mean(X,2);

% K = (X'*X+1).^d;
% K_te = (X'*X_te+1).^d;
% N = size(Y,1);
% pred = Y / (K+lambda*eye(N)) * K_te;

for d = 1:D
    X_te(d,fix_idx{d}) = mean_val(d);
end

if d == 1
    new_X = X;
    new_X_te = X_te;
end

cc = D;

if d >= 2
    new_X = X;
    
    for i = 1:D
        for j = i:D
            new_X = [new_X; X(i,:).*X(j,:)];
        end
    end
    
    new_X_te = X_te;
    
    for i = 1:D
        for j = i:D
            new_X_te = [new_X_te; X_te(i,:).*X_te(j,:)];
        end
    end
end

if d == 3
    
    for i = 1:D
        for j = i:D
            for p = j:D
                new_X = [new_X; X(i,:).*X(j,:).*X(p,:)];
            end
        end
    end
    
    for i = 1:D
        for j = i:D
            for p = j:D
                new_X_te = [new_X_te; X_te(i,:).*X_te(j,:).*X_te(p,:)];
            end
        end
    end
end

new_X = [new_X; ones(1,size(new_X,2))];
new_X_te = [new_X_te; ones(1,size(new_X_te,2))];
w = inv(new_X*new_X'+lambda*eye(size(new_X,1)))*new_X*Y';
pred = w'*new_X_te;