function ratio=rowknn(k,training, testing)
  classes=rowfun(@(row)(findclass(row,k,training)),testing);
  labels = test(:,1)
  correct=length(find(classes == labels));
  ratio = correct/rows(testing);
endfunction