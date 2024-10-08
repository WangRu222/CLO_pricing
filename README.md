# What is CLO product

The asset pool is divided into two ends, one end is the underlying assets (asset side), and the other end is the investors (securities side). The common mechanism is as follows: The cash flow generated by the underlying assets flows from the asset side into the securitized asset pool (cash inflow), and after being collected, it is paid to the investors on the securities side on the interest payment date (cash outflow).

# The cash flow of Asset side

For the convenience of description, we consider that within a natural year and 12 months, there are N delivery dates on the asset side, which are ${T_i}|_{i=1}^{i=N}$, (uniformly distributed)

- Given the annualized early repayment rate CPR, calculate the current early repayment amount $C_i$:

$SMM_i$ is the single-period early repayment rate, $C_i$ is the early repayment amount of the $i$th period, $X_{i-1}$ is the balance at the end of the previous period (i-1th period), and $A_i^0$ is the principal to be repaid in this period (0 early repayment and 0 default).

$$
SMM_i=\frac{C_i}{X_{i-1}-A_{i}^0}
$$

Assuming that the single-period early repayment rate $SMM_i$ is fixed as a constant, the formula for the annualized early repayment rate CPR is:

$$
CPR= 1-(1-SMM_i)^{N},
$$

When the annualized early repayment rate is given, according to \eqref{SMM}\eqref{cpr}, we can calculate the early repayment amount $C_i$ for each period: 

$$
C_i=[1-(1-CPR)^{\frac{1}{N}}]*(X_{i-1}-A_i^0)
$$

- Given the annualized default rate DR, calculate the current default amount $D_i$: 
Where $D_i$ is the default amount up to the i-th period, $X_{i-1}$ is the total outstanding amount at the beginning of the i-th period.

Given the annualized default rate DR, $D_i$ can be calculated as:

$$
D_i=DR * X_{i-1}* \frac{day_{i}}{365}
$$

Where $day_i=T_i-T_{i-1}$ is the number of days in the current period (interest-bearing days)

# The cash flow from asset side to securities

From the previous part, the total amount $Sum_i$ of interest recovery and principal recovery in period $i$ on the asset side is obtained, which will be used to sequentially pay various expenditures on the securities side in period $i$.
- Tax $Tax_i$
During the redemption process, a certain amount of tax will be incurred, which is 0.45% of $Sum_i$

$$
    Tax_i=0.45* \% * Sum_{i}
$$


- Interest on senior bonds $I_{1,i}$
    
Given the ending balance $X_{i-1}$ of period $i-1$ on the securities side, we can get the priority payment interest $I_{1,i}$ of period $i$:

$$
    I_{1,i}=r * X_{i-1}* \frac{T_i-DATE}{365}
$$

Where DATE is the interest accrual date of the bond.

- Interest on subordinated bonds $I_{2,i}$

Before the principal of the senior bonds has been paid, the subordinated bonds will only pay interest, which is 2% of the total amount of the subordinated bonds.



- Pricing Based on Principal amount of senior bonds $A_i$
  
$$
    A_i=Sum_i-Tax_i-I_{1,i}-I_{2,i}
$$

At this point, the ending balance of the $i$th period on the securities side can be obtained $X_i=X_{i-1}-A_i$.
All cash flows on the securities side can be obtained in sequence

# Discounted Cash Flow Method

The cash flow $Y_i$ of the security side in period $i$ is the sum of interest $I_i$ and principal $A_i$:

$$
    Y_i=I_i+A_i
$$


By Discounted Cash Flow Method, we can get：

$$
P_{DATE}=\frac{Y_1}{(1+\frac{r}{N_0})^{\frac{T_1-DATE}{T_1-T_0}}}+\frac{Y_2}{(1+\frac{r}{N_0})^{\frac{T_2-DATE}{T_2-T_1}}}+\cdots+ \frac{Y_N}{(1+\frac{r}{N_0})^{\frac{T_N-DATE}{T_N-T_{N-1}}}}
$$

so

$$
    P_{DATE}=\sum_{i=1}^{i=N}\frac{Y_i}{(1+\frac{r}{N_0})^{\frac{T_i-DATE}{T_i-T_{i-1}}}}
$$
