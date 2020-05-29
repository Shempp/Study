function plotTour(OptTour,OptimalDistance,EucCoords)
figure(1)
% ���������� ������������ ����
coordsOptTour=zeros(length(OptTour),2);
for i=1:length(OptTour)
    coordsOptTour(i,:)=EucCoords(OptTour(i),:);
end
% ��������� ��������� �������
coordsOptTour(length(coordsOptTour),:)=EucCoords(OptTour(1),:);
% ������
nexttile
plot(coordsOptTour(:,1),coordsOptTour(:,2),'o-','Color','b','MarkerFaceColor','r','MarkerEdgeColor','k','MarkerSize',4);
title("Berlin52 Tour. Distance = "+sprintf('%.4f',OptimalDistance));
end

