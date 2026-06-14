function plot_response(H_expr, omega_sym, params, param_vals, freq_start, freq_stop, min_gain_bands, max_gain_bands)
    omegas = logspace(log10(freq_start * 2*pi), log10(freq_stop * 2*pi), 1000);
    H_db   = zeros(1, numel(omegas));
    for k = 1:numel(omegas)
        H_at_omega = subs(H_expr, omega_sym, omegas(k));
        H_db(k)    = 20 * log10(abs(double(subs(H_at_omega, params, param_vals))));
    end

    semilogx(omegas / (2*pi), H_db, 'b', 'LineWidth', 1.5);
    hold on;

    %for band = 1:size(min_gain_bands, 1)
    %    xline(min_gain_bands(band,1), '--g');
    %    xline(min_gain_bands(band,2), '--g');
    %    yline(min_gain_bands(band,3), '--g', sprintf('Min %.0fdB', min_gain_bands(band,3)));
    %end
    %for band = 1:size(max_gain_bands, 1)
    %    xline(max_gain_bands(band,1), '--r');
    %    xline(max_gain_bands(band,2), '--r');
    %    yline(max_gain_bands(band,3), '--r', sprintf('Max %.0fdB', max_gain_bands(band,3)));
    %end

    hold off;
    xlabel('Frequency (Hz)'); ylabel('Gain (dB)');
    title('Filter Response'); grid on;
end