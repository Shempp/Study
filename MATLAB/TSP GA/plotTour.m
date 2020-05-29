function plotTour(OptTour,OptimalDistance,EucCoords)
figure(1)
% Координаты оптимального тура
coordsOptTour=zeros(length(OptTour),2);
for i=1:length(OptTour)
    coordsOptTour(i,:)=EucCoords(OptTour(i),:);
end
% Соединяем последний элемент
coordsOptTour(length(coordsOptTour),:)=EucCoords(OptTour(1),:);
% График
nexttile
plot(coordsOptTour(:,1),coordsOptTour(:,2),'o-','Color','b','MarkerFaceColor','r','MarkerEdgeColor','k','MarkerSize',4);
title("Berlin52 Tour. Distance = "+sprintf('%.4f',OptimalDistance));
end

