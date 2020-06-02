from rest_framework import serializers
from .models import RentingItem

class RentingItemSerializer(serializers.HyperlinkedModelSerializer):
    class Meta:
        model = RentingItem
        fields = ['id', 'price', 'address', 'pub_date']