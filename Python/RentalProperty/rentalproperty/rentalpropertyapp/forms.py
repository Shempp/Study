from django import forms

class RentalPropertyAddForm(forms.Form):
    price = forms.IntegerField()
    address = forms.CharField(label='Your name', max_length=256)