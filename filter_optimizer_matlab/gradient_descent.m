function param_vals = gradient_descent(H_expr, omega_sym, params, param_vals, ...
                                        min_gain_bands, max_gain_bands, ...
                                        learning_rate, learning_steps)
    for step = 1:learning_steps

        for band = 1:size(min_gain_bands, 1)
            freqs = logspace(log10(min_gain_bands(band,1) * 2*pi), ...
                             log10(min_gain_bands(band,2) * 2*pi), 100);
            grads = compute_gradients(H_expr, omega_sym, params, param_vals, freqs, ...
                                      min_gain_bands(band,3), true);
            param_vals = 10.^(log10(param_vals) - learning_rate .* grads ./ 10);
        end

        for band = 1:size(max_gain_bands, 1)
            freqs = logspace(log10(max_gain_bands(band,1) * 2*pi), ...
                             log10(max_gain_bands(band,2) * 2*pi), 100);
            grads = compute_gradients(H_expr, omega_sym, params, param_vals, freqs, ...
                                      max_gain_bands(band,3), false);
            param_vals = 10.^(log10(param_vals) - learning_rate .* grads ./ 10);
        end

        %if mod(step, 100) == 0
            fprintf('Step %4d | params: %s\n', step, mat2str(param_vals, 4));
        %end
    end
end