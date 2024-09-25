# What is CLO product

FITCH IBCA defines a bank CLO as a security issued by an entity that purchases or references loans from
the banking institution which sponsors the transaction. Loans are typically originated by the sponsor and serve
as collateral for the notes and certificates issued. There are also nonbank participants issuing CLOs with the
motivation of spread arbitrage derived from an asset mix of high-yield and distressed loans. In bank CLOs, the
motivation is to reduce capital requirements and fund low-yielding assets. The underlying collateral is composed
mostly of investment-grade and some non- investment-grade corporate loans. There are generally several tranches
of rated securities, as well as an unrated equity tranche commonly retained by the bank.

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
