'use strict';

// TODO: not used for now
// Testing controller
describe('RentingItemsListController', function() {
    // Before each test we tell AngularJS to load the rentalpropertyApp module
  beforeEach(module('rentalpropertyApp'));

  // We ask AngularJS to inject the $controller service into our test function
  it('should create a `rentingItems` model with 3 renting items', inject(function($controller) {
    var scope = {};
    // We use $controller to create an instance of the RentingItemsListController
    var ctrl = $controller('RentingItemsListController', {$scope: scope});

    // With this instance, we verify that the rentingItems array property on the scope contains three records
    expect(scope.rentingItems.length).toBe(3);
  }));

});