// lf = (scalar(1) + sign(T-Tm))/scalar(2);

// lf0 = lf;

 DH = DHnew;

 forAll(mesh.cells(),celli)
    {

       if (DH[celli] > L.value())
          {
             DH[celli] = L.value();
          }
       if (DH[celli] < 0)
          {
             DH[celli] = 0;
          }

    };

  lf=DH/L;

 A = -C*sqr(scalar(1)-lf)/(rho*(pow(lf,scalar(3))+scalar(1e-6)));

