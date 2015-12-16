Data=[1   0.180831826;
      1   0.180342651;
      1   0.17088175;
      1.5 0.266666667;
      1.5 0.259403372;
      1.5 0.254452926;
      2	  0.265957447;
      2   0.284090909;
      2	  0.37037037;
      2.5 0.344827586;
      2.5 0.294117647;
      2.5 0.291970803;
      3	  0.362318841;
      3   0.256410256;
      3.5 0.840336134;
      3.5 0.549450549;
      3.5 0.476190476;
      4	  0.549450549];
avgLine=[1 0.18;1.5 0.325; 3 0.325; 4 0.7];
  
scatter(Data(:,1),Data(:,2),'*');
hold;
plot(avgLine(:,1),avgLine(:,2),'linewidth',2);
legend('Data points', 'Stepwise Average','location','southeast')
grid on
set(gca,'GridLineStyle',':', 'GridColor', 'k', 'GridAlpha', .6)
title('K_{steering} vs K_p')
xlabel('K_p','fontsize',14)
ylabel('K_{steering}','fontsize',14)