%function [H_expr, omega_sym, params, param_vals] = filter_definition()
%    syms R C omega real;

%    Z_C = 1 / (1j * omega * C);
%    Z_load = 50;
%    Z_parallel = (Z_C * Z_load) / (Z_C + Z_load);

%    H_expr    = abs(Z_parallel / (Z_parallel + R));  % raw expression, no syms function wrapper

%    omega_sym  = omega;
%    params     = [R, C];
%    param_vals = [1, 1];
%end

function [H_expr, omega_sym, params, param_vals] = filter_definition()
    % Gradient descent test
    syms R C omega real;

    H_expr    = abs(Z_parallel / (Z_parallel + R));  % raw expression, no syms function wrapper

    omega_sym  = omega;
    params     = [R, C];
    param_vals = [1, 1];
end