function grad_vals = compute_gradients(H_expr, omega_sym, params, param_vals, freqs, db_limit, db_limit_is_min)
    grad_vals = zeros(1, numel(params));

    dH = cell(1, numel(params));
    for i = 1:numel(params)
        dH{i} = diff(H_expr, params(i));
    end

    for f_idx = 1:numel(freqs)
        omega_val  = freqs(f_idx);

        H_at_omega = subs(H_expr, omega_sym, omega_val);
        H_num      = double(subs(H_at_omega, params, param_vals));
        H_db_val   = 20 * log10(abs(H_num));

        past_limit = H_db_val > db_limit;
        if xor(past_limit, ~db_limit_is_min)
            for i = 1:numel(params)
                dH_at_omega = subs(dH{i}, omega_sym, omega_val);
                dH_num      = double(subs(dH_at_omega, params, param_vals));
                dHdb_dp     = (20 / log(10)) * real(dH_num) / abs(H_num);
                grad_vals(i) = grad_vals(i) + 2 * (H_db_val - db_limit) * dHdb_dp;
            end
        end
    end
end