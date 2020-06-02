from rest_framework import viewsets
from .serializers import RentingItemSerializer
from .models import RentingItem
from django.shortcuts import render

# Create your views here.

class RentingItemViewSet(viewsets.ModelViewSet):
    """
    API endpoint that allows users to be viewed or edited.
    """
    queryset = RentingItem.objects.all().order_by('id')
    serializer_class = RentingItemSerializer

def home(request):
    return render(request, 'base.html')