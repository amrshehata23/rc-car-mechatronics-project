%% RC Car Speed Response Simulation
% This script simulates a simplified RC car speed response using a
% first-order dynamic system.
%
% Project: RC Car Mechatronics Project
% Tool: MATLAB
% Topic: Vehicle behavior, motor response, and system optimization
%
% Model:
% v(t) = Vmax * (1 - exp(-t/tau))

clear;
clc;
close all;

%% System Parameters
targetSpeed = 2.5;      % Maximum target speed [m/s]
tau = 1.2;              % Time constant [s]

tStart = 0;             % Start time [s]
tEnd = 10;              % End time [s]
dt = 0.01;              % Time step [s]

settlingBand = 0.02;    % 2 percent settling band

%% Input Validation
if targetSpeed <= 0
    error('Target speed must be greater than zero.');
end

if tau <= 0
    error('Time constant tau must be greater than zero.');
end

if dt <= 0 || tEnd <= tStart
    error('Check simulation time settings.');
end

%% Time Vector
time = tStart:dt:tEnd;

%% Speed Response Model
speed = targetSpeed * (1 - exp(-time / tau));

%% Acceleration Calculation
% Analytical acceleration for a first-order response
acceleration = (targetSpeed / tau) * exp(-time / tau);

%% Distance Calculation
% Analytical distance for a first-order speed response
distance = targetSpeed * (time - tau * (1 - exp(-time / tau)));

%% Performance Metrics
finalSpeed = speed(end);
finalDistance = distance(end);
maxAcceleration = max(acceleration);

riseSpeed90 = 0.90 * targetSpeed;
riseIndex = find(speed >= riseSpeed90, 1, 'first');

if isempty(riseIndex)
    riseTime90 = NaN;
else
    riseTime90 = time(riseIndex);
end

settlingLowerLimit = targetSpeed * (1 - settlingBand);
settlingIndex = find(speed >= settlingLowerLimit, 1, 'first');

if isempty(settlingIndex)
    settlingTime = NaN;
else
    settlingTime = time(settlingIndex);
end

steadyStateError = targetSpeed - finalSpeed;

%% Plot Results
figure('Name', 'RC Car Speed Response');
plot(time, speed, 'LineWidth', 2);
hold on;
yline(targetSpeed, '--', 'Target Speed', 'LineWidth', 1.5);
yline(riseSpeed90, '--', '90% Speed', 'LineWidth', 1);
grid on;
xlabel('Time [s]');
ylabel('Speed [m/s]');
title('RC Car Speed Response');

figure('Name', 'RC Car Acceleration');
plot(time, acceleration, 'LineWidth', 2);
grid on;
xlabel('Time [s]');
ylabel('Acceleration [m/s^2]');
title('RC Car Acceleration');

figure('Name', 'RC Car Distance');
plot(time, distance, 'LineWidth', 2);
grid on;
xlabel('Time [s]');
ylabel('Distance [m]');
title('RC Car Distance Over Time');

%% Display Results
fprintf('RC Car Simulation Results:\n');
fprintf('--------------------------\n');
fprintf('Target speed: %.2f m/s\n', targetSpeed);
fprintf('Final speed: %.2f m/s\n', finalSpeed);
fprintf('Final distance: %.2f m\n', finalDistance);
fprintf('Maximum acceleration: %.2f m/s^2\n', maxAcceleration);
fprintf('90%% rise time: %.2f s\n', riseTime90);
fprintf('2%% settling time: %.2f s\n', settlingTime);
fprintf('Steady-state error at %.2f s: %.4f m/s\n', tEnd, steadyStateError);
