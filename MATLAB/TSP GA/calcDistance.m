function [Distance] = calcDistance(Tour,DistanceMatrix)
Distance=0;
TourLength=length(Tour);

for i=2:TourLength
    Distance=Distance+DistanceMatrix(Tour(i),Tour(i-1));
end

% ����� ��������� ��������� ���� �� �������� ����� (����� ������� - 1)
Distance=Distance+DistanceMatrix(Tour(TourLength),Tour(1));

end

