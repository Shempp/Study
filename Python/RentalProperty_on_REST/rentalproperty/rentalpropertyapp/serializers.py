from rest_framework import serializers
from .models import RentingItem

class RentingItemSerializer(serializers.HyperlinkedModelSerializer):
    id = serializers.ReadOnlyField()
    pub_date = serializers.ReadOnlyField()
    class Meta:
        model = RentingItem
        fields = ['id', 'price', 'address', 'pub_date']