function plotEasomFunc(Xmin, Fxmin, XminGen, FxminGen)
% Размер шрифта
PlotFontSize=10;
% Нижние границы координат
XLowerBounds=1;
% Верхние границы координат
XUpperBounds=5;
% Шаг
Step=0.1;
XData1=XLowerBounds:Step:XUpperBounds;
XData2=XLowerBounds:Step:XUpperBounds;
[XXData1, XXData2] = meshgrid(XData1 ,XData2);
YYData=easomFuncForPlot(XXData1, XXData2);
% Прорисовка фигуры в отдельном окне
figure(2);
meshc(XXData1, XXData2, YYData);
colorbar
set(gca,'fontsize',PlotFontSize);
xlabel('x1','fontsize',PlotFontSize);
ylabel('x2','fontsize',PlotFontSize);
zlabel('f','fontsize',PlotFontSize);
axis tight
% Добавление точки экстремума
hold on
plot3(Xmin(1),Xmin(2),Fxmin,'r.','MarkerSize',20)
% Добавление промежуточных точек популяции
for i=1:length(XminGen)
    plot3(XminGen(i,1),XminGen(i,2),FxminGen(i),'b.','MarkerSize',10)
end
hold off
end

function [YData] = easomFuncForPlot(x1, x2)
fact1 = -cos(x1).*cos(x2);
fact2 = exp(-(x1-pi).^2-(x2-pi).^2);
YData = fact1.*fact2;
end