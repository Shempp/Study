from rest_framework import viewsets
from .serializers import RentingItem

# Create your views here.

class RentingItemViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = RentingItem.objects.all().order_by('id')
    serializer_class = RentingItem