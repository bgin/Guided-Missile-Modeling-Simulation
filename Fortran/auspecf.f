      SUBROUTINE AUSPECF(N,LAGH1,CXX1,P1,P2,Q)
C
      
C
C     PROGRAM 5.2.1   POWER SPECTRUM
C-----------------------------------------------------------------------
C     ** DESIGNED BY H. AKAIKE, THE INSTITUTE OF STATISTICAL MATHEMATICS
C     ** PROGRAMMED BY E. ARAHATA, THE INSTITUTE OF STATISTICAL MATHEMAT
C        TOKYO
C     ** DATE OF THE LATEST REVISION: MARCH 25, 1977
C     ** THIS PROGRAM WAS ORIGINALLY PUBLISHED IN
C        "DAINAMIKKU SISTEMU NO TOKEI-TEKI KAISEKI TO SEIGYO (STATISTICA
C        ANALYSIS AND CONTROL OF DYNAMIC SYSTEMS)" BY H. AKAIKE AND
C        T. NAKAGAWA, SAIENSU-SHA, TOKYO, 1972 (IN JAPANESE)
C-----------------------------------------------------------------------
C     THIS PROGRAM COMPUTES POWER SPECTRUM ESTIMATES FOR TWO
C     TRIGONOMETRIC WINDOWS OF BLACKMAN-TUKEY TYPE BY GOERTZEL METHOD.
C     ONLY ONE CARD OF LAGH(MAXIMUM LAG OF COVARIANCES TO BE USED FOR
C     POWER SPECTRUM COMPUTATION) SHOULD BE ADDED ON TOP OF THE OUTPUT
C     OF PROGRAM 5.1.1 AUTCOR TO FORM INPUT TO THIS PROGRAM.
C     OUTPUTS ARE ESTIMATES P1(I),P2(I) FOR FREQUENCIES I/(2LAGH*DELTAT)
C     AND THE TEST STATISTICS Q(I) FOR THE DIFFERENCES BETWEEN P1(I) AND
C     P2(I).   Q(I) GREATER THAN 1 MEANS SIGNIFICANT DIFFERENCE.
C
cc      !DEC$ ATTRIBUTES DLLEXPORT :: AUSPECF
c      USE DFLIB
C
cxx      IMPLICIT REAL*8(A-H,O-Z)
c      DIMENSION CXX(1001),FC(1001),P1(1001),P2(1001),Q(1001)
c      DIMENSION A1(10),A2(10)
cxx      DIMENSION CXX1(LAGH1),CXX(LAGH1)
cxx      DIMENSION FC(LAGH1),P1(LAGH1),P2(LAGH1),Q(LAGH1)
cxx      DIMENSION A1(2),A2(3)
      INTEGER :: N, LAGH1
      REAL(8) :: CXX1(LAGH1), P1(LAGH1), P2(LAGH1), Q(LAGH1)
      REAL(8) :: CXX(LAGH1), FC(LAGH1), A1(2), A2(3)
C
C     INPUT / OUTPUT DATA FILE OPEN
c	CHARACTER(100) DFNAM
c	DFNAM='auspec.out'
c	CALL SETWND
c	CALL FLOPN3(DFNAM,NFL)
c	IF (NFL.EQ.0) GO TO 999
C
C     WINDOW W1 DEFINITION
      MLA1=2
      A1(1)=0.5D-00
      A1(2)=0.25D-00
C     WINDOW W2 DEFINITION
      MLA2=3
      A2(1)=0.625D-00
      A2(2)=0.25D-00
      A2(3)=-0.0625D-00
C
C     LAGH SPECIFICATION
c      READ(5,1) LAGH
c      LAGH1=LAGH+1
C     READING THE OUTPUTS OF PROGRAM 5.1.1 AUTCOR
c      READ(5,1) N,LAGH0
c      LAGH3=LAGH0+1
C     INITIAL CONDITION PRINT OUT
c      WRITE(6,60)
c      WRITE(6,61)
c      WRITE(6,62) N,LAGH
c      WRITE(6,63)
c      CALL PRCOL1(A1,1,MLA1,1)
c      WRITE(6,64)
c      CALL PRCOL1(A2,1,MLA2,1)
C     AUTO COVARIANCE INPUT
c      READ(5,2) (CXX(I),I=1,LAGH3)
C     AUTO COVARIANCE PRINT OUT
c      WRITE(6,172)
c      WRITE(6,162)
c      CALL PRCOL1(CXX,1,LAGH1,1)
c      DO 10 I=2,LAGH
c   10 CXX(I)=CXX(I)+CXX(I)
      CXX(1)=CXX1(1)
      DO 10 I=2,LAGH1-1
cxx   10 CXX(I)=CXX1(I)+CXX1(I)
      CXX(I)=CXX1(I)+CXX1(I)
   10 CONTINUE
      CXX(LAGH1)=CXX1(LAGH1)
C     F-COS TRANSFORMATION
      CALL FGERCO(CXX,LAGH1,FC,LAGH1)
C     SPECTRUM SMOOTHING BY WINDOW W1
      CALL AUSP(FC,P1,LAGH1,A1,MLA1)
C     SPECTRUM SMOOTHING BY WINDOW W2
      CALL AUSP(FC,P2,LAGH1,A2,MLA2)
C     TEST STATISTICS COMPUTATION
      CALL SIGNIF(P1,P2,Q,LAGH1,N)
C     AUTO SPECTRUM AND TEST STATISTICS PRINT OUT
c      WRITE(6,66) N,LAGH
c      WRITE(6,67)
c      CALL PRCOL3(P1,P2,Q,1,LAGH1,1)
C     AUTO SPECTRUM SMOOTHED BY WINDOW W1 PUNCH OUT
c      WRITE(7,1) N,LAGH
c      WRITE(7,2) (P1(I),I=1,LAGH1)
c	CALL FLCLS3(NFL)
c    1 FORMAT(10I5)
c    2 FORMAT(4D20.10)
c   60 FORMAT(1H ,30HPROGRAM 5.2.1   POWER SPECTRUM)
c   62 FORMAT(1H ,2HN=,I5,5X,5HLAGH=,I5)
c   61 FORMAT(1H ,17HINITIAL CONDITION)
c   63 FORMAT(1H ,12X,9HWINDOW W1/1H ,4X,1HI,11X,5HA1(I))
c   64 FORMAT(1H ,12X,9HWINDOW W2/1H ,4X,1HI,11X,5HA2(I))
c   66 FORMAT(//1H ,14HPOWER SPECTRUM,5X,2HN=,I5,5X,5HLAGH=,I5)
c   67 FORMAT(1H ,4X,1HI,8X,8HPOWER W1,6X,8HPOWER W2,2X,12HSIGNIFICANCE)
c  162 FORMAT(1H ,4X,1HI,6X,6HCXX(I))
c  172 FORMAT(1H ,5X,15HAUTO COVARIANCE)
      RETURN
      END SUBROUTINE
