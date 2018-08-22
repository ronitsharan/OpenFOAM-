// Solve energy equation

        ST = fvc::ddt(DH)/Cp;
        STconv = fvc::div(phi, DH)/Cp;

        tmp<fvScalarMatrix> TEqn
        (
            fvm::ddt(T)
          + fvm::div(phi, T)
          - fvm::laplacian(DT, T)
         == 
          - ST
	  - STconv 
        );

        TEqn().relax();

        eqnResidual = solve(TEqn()).initialResidual();
        maxResidual = max(eqnResidual, maxResidual);

        resT << runTime.timeName() << "   " << iter << "   " << eqnResidual << endl;

        rho = rho0*(scalar(1) - beta*(T - T0));

        volVectorField gradT = fvc::grad(T);
        volScalarField dTdx = gradT.component(vector::X);

        h = Cp*T;

	volScalarField Tstar = (Tl - Ts)*lf + Ts;

        DHnew = DH + omegaDH*(h - Cp*Tstar);
