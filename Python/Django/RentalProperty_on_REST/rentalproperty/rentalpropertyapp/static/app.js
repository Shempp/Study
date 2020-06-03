'use strict';

// Define the `rentalpropertyApp` module
// TODO: add bound forms support for AngularJS ('djng.forms')?
var rentalpropertyApp = angular.module('rentalpropertyApp', [/*'djng.forms'*/]);

// As a convention in web applications, Ajax requests shall send the HTTP-Header (X-Requested-With: XMLHttpRequest)
rentalpropertyApp.config(function($httpProvider) {
    $httpProvider.defaults.headers.common['X-Requested-With'] = 'XMLHttpRequest';
});

// TODO: add time in 'rentingItems' model
// Define the `RentingItemsListController` controller on the `rentalpropertyApp` module
rentalpropertyApp.controller('RentingItemsListController', function RentingItemsListController($scope) {
    $scope.rentingItems = [
        {
            name: 'Saint-Petersburg, st. Begovaya, 10',
            price: '25000'
        }, {
            name: 'Saint-Petersburg, st. Begovaya, 11',
            price: '20000'
        }, {
            name: 'Saint-Petersburg, st. Begovaya, 12',
            price: '15000'
        }
    ];
});