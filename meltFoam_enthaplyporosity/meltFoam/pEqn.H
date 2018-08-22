            p.boundaryField().updateCoeffs();
            volScalarField rUA = 1.0/UEqn().A();

            U = rUA*UEqn().H();
            UEqn.clear();
            phi = fvc::interpolate(U) & mesh.Sf();
            adjustPhi(phi, U, p);

            // Store pressure for under-relaxation
            p.storePrevIter();

            // Non-orthogonal pressure corrector loop
            for (int nonOrth=0; nonOrth<=nNonOrthCorr; nonOrth++)
            {
                fvScalarMatrix pEqn
                (
                    fvm::laplacian(rUA, p) == fvc::div(phi)
                );

                pEqn.setReference(pRefCell, pRefValue);
//                pEqn.solve();

                if (nonOrth == 0)
                {
                eqnResidual = pEqn.solve().initialResidual();
                maxResidual = max(eqnResidual, maxResidual);
		
		resP << runTime.timeName() << "   " << iter << "   " << eqnResidual << endl;

                }
                else
                {
                pEqn.solve();
                }


                if (nonOrth == nNonOrthCorr)
                {
                    phi -= pEqn.flux();
                }
            }

#           include "continuityErrs.H"

            // Explicitly relax pressure for momentum corrector
            p.relax();

            // Momentum corrector
            U -= rUA*fvc::grad(p);
            U.correctBoundaryConditions();

