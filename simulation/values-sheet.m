%%%%%%%%%%%% Motor %%%%%%%%%%%%

R = 0.178;      % The motor's internal resistance [Ohm]
L = 119.26e-6;  % The motor's inductance [H]
Ke = 1.89e-3;   % the electromotive constant [Wb]
Kt = 0.0016;    % The motor constant [Wb]
Jm = 2.3891e-6; % Motor's inertia [kg.m^2]
Bm = 2.2e-6;    % Motor's friction [N.m.s]

%%%%%%%%%%%% DriveTrain %%%%%%%

rt = 0.166/(2*pi);  % Meters traveled (by the vehicle) by rotation of the drive wheel
N = 4773/187;       % Gear ratio of drivetrain excluding belt
rm = 4.66e-3;       % Diameter of motor gear [m]
rd = N * rm         % Diameter of 'imaginary' drivetrain gear [m]

%Nm = 17;        % Number of teeth on the gear Gm (on motor shaft)
%Nd = Nm * N;

%%%%%%%%%%%% Total system %%%%%%

Rbat = 0;     % Internal resistance of the battery (measured to be 0.11 ?) [Ohm]
M = 2.932;    % Total mass of the vehicle [kg]

tau = 0.207; % Time constant of the whole system measured from step-response (old value : 0.258s) [s]

Btot = 4.7088e-06; % Total friction of the system [N.m.s]
Jtot = 4.5782e-06; % Old value : 5.5980e-06 [kg.m^2]