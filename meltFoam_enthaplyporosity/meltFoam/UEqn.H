
// Momentum predictor

SU = A*U;

tmp<fvVectorMatrix> UEqn
(
   fvm::ddt(U)
 + fvm::div(phi, U)
 - fvm::laplacian(nu, U)
 - fvm::Sp(A, U)
==
  -beta*(T - T0)*g
);

UEqn().relax();

//solve(UEqn() == -fvc::grad(p));
eqnResidual = solve(UEqn() == -fvc::grad(p)).initialResidual();
maxResidual = max(eqnResidual, maxResidual);

resU << runTime.timeName() << "   " << iter << "   " << eqnResidual << endl;

