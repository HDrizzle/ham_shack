freq_start     = 1;
freq_stop      = 1000;
learning_rate  = 0.0001;
learning_steps = 10;

%min_gain_bands = [1,   100,  -3 ];
%max_gain_bands = [150, 1000, -20];

min_gain_bands = [1, 1000, -1];
max_gain_bands = [1, 1000, 0];

[H_expr, omega_sym, params, param_vals] = filter_definition();

param_vals = gradient_descent(H_expr, omega_sym, params, param_vals, ...
                               min_gain_bands, max_gain_bands, ...
                               learning_rate, learning_steps);

fprintf('Final params: %s\n', mat2str(param_vals, 6));
plot_response(H_expr, omega_sym, params, param_vals, freq_start, freq_stop, min_gain_bands, max_gain_bands);