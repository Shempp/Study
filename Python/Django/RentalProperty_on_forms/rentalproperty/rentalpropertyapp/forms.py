from django import forms

class RentalPropertyAddForm(forms.Form):
    price = forms.IntegerField(label='Цена')
    address = forms.CharField(label='Адрес', max_length=32)